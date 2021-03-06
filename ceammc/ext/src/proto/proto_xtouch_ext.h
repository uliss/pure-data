/*****************************************************************************
 * Copyright 2020 Serge Poltavsky. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#ifndef HW_XTOUCH_EXT_H
#define HW_XTOUCH_EXT_H

#include "ceammc_object.h"
#include "ceammc_property_enum.h"

#include <array>
#include <cstdint>
#include <string>

using namespace ceammc;

class Display {
public:
    static const uint8_t MAX_CHARS = 7;

    enum Mode : uint8_t {
        MODE_INVERTED = 0,
        MODE_INVERTED_UPPER = 1,
        MODE_INVERTED_LOWER = 2,
        MODE_NORMAL = 3
    };

    enum Color : uint8_t {
        BLACK = 0,
        RED = 1,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        NUM_COLORS,
        UNKNOWN = NUM_COLORS
    };

    enum Align : uint8_t {
        ALIGN_CENTER,
        ALIGN_LEFT,
        ALIGN_RIGHT,
        ALIGN_JUSTIFY,
        ALIGN_AUTO,
        ALIGN_INVALID
    };

    enum {
        MODE_MIN = MODE_INVERTED,
        MODE_MAX = MODE_NORMAL,
        COLOR_MIN = BLACK,
        COLOR_MAX = WHITE,
        ALIGN_MIN = ALIGN_CENTER,
        ALIGN_MAX = ALIGN_AUTO
    };

    Display()
        : color_(CYAN)
        , mode_(MODE_INVERTED)
        , upper_align_(ALIGN_AUTO)
        , lower_align_(ALIGN_AUTO)
    {
    }

    char upperCharAt(uint8_t pos) const { return (pos < MAX_CHARS) ? txt_[pos] : 0; }
    char lowerCharAt(uint8_t pos) const { return (pos < MAX_CHARS) ? txt_[pos + MAX_CHARS] : 0; }

    void setUpperText(const char* str);
    void setUpperText(const AtomListView& atoms);
    void setLowerText(const char* str);
    void setLowerText(const AtomListView& atoms);
    std::string upperText() const;
    std::string lowerText() const;

    void setUpperAlign(Align a) { upper_align_ = a; }
    bool setUpperAlign(const Atom& a);
    void setLowerAlign(Align a) { lower_align_ = a; }
    bool setLowerAlign(const Atom& a);
    Align upperAlign() const { return upper_align_; }
    Align lowerAlign() const { return lower_align_; }

    void clearUpper();
    void clearLower();
    void clearBoth();
    void setDefault();

    uint8_t packedColorMode() const { return color_ | (mode_ << 4); }

    Color color() const { return color_; }
    void setColor(Color c) { color_ = c; }
    bool setColor(const Atom& a);

    void setMode(Mode m) { mode_ = m; }

public:
    static Color randomColor();
    static Color namedColor(const t_symbol* c);

    /**
     * converts align name to enum value
     * @return ALIGN_INVALID if not found
     */
    static Align namedAlign(const t_symbol* a);

private:
    char txt_[2 * MAX_CHARS] = { 0 };
    Color color_;
    Mode mode_;
    Align upper_align_, lower_align_;

private:
    static void setCentered(char* dest, const char* txt);
    static void setAlignedLeft(char* dest, const char* txt);
    static void setAlignedRight(char* dest, const char* txt);
    static void setJustified(char* dest, const char* txt);
};

enum MidiFSMState {
    MIDI_FSM_STATE_INIT = 0,
    MIDI_FSM_STATE_NOTE_OFF = 0x80,
    MIDI_FSM_STATE_NOTE_ON = 0x90,
    MIDI_FSM_STATE_CONTROLCHANGE = 0xb0,
};

struct MidiFSMParser {
    MidiFSMState state = { MIDI_FSM_STATE_INIT };
    const static uint8_t max_data_len = { 3 };
    uint8_t data[max_data_len];
    uint8_t size = { 0 };

    void reset()
    {
        state = MIDI_FSM_STATE_INIT;
        size = 0;
    }

    void appendData(uint8_t v)
    {
        if (size >= max_data_len)
            return reset();

        data[size++] = v;
    }

    bool isReady() const { return size == max_data_len; }
    bool isCC() const { return isReady() && ((data[0] & 0xf0) == MIDI_FSM_STATE_CONTROLCHANGE); }
    bool isNoteOn() const { return isReady() && ((data[0] & 0xf0) == MIDI_FSM_STATE_NOTE_ON); }
    uint8_t channel() const { return data[0] & 0x0f; }
};

class Button {
public:
    enum State {
        ACTIVE = -1,
        OFF = 0,
        ON = 1
    };

    enum Mode {
        BUTTON,
        TOGGLE
    };

    using ButtonFn = std::function<void(int)>;

    Button(State st = OFF)
        : state_(st)
        , mode_(TOGGLE)
    {
    }

    State state() const { return state_; }
    void setState(State st);
    bool setState(const Atom& a);
    bool setMode(const Atom& a);
    void setMidi(int vel);

    void toggle();

    bool isActive() const { return state_ == ACTIVE; }
    bool isOff() const { return state_ == OFF; }
    bool isOn() const { return state_ == ON; }

    void setFn(ButtonFn fn) { fn_ = fn; }

private:
    ButtonFn fn_;
    State state_;
    Mode mode_;
};

class Fader {
public:
    using FaderFn = std::function<void(t_float)>;

    Fader(t_float v = 0)
        : v_(v)
    {
    }

    t_float value() const { return v_; }
    void setValue(t_float v);
    bool setValue(const Atom& a);

    void setFn(FaderFn fn) { fn_ = fn; }

private:
    FaderFn fn_;
    t_float v_;
};

struct Scene {
    static constexpr int NCHAN = 8;
    std::array<Fader, NCHAN> faders_;
    std::array<Fader, NCHAN> knobs_;
    std::array<Button, NCHAN> btn_rec_;
    std::array<Button, NCHAN> btn_solo_;
    std::array<Button, NCHAN> btn_mute_;
    std::array<Button, NCHAN> btn_select_;
    std::array<bool, NCHAN> fader_is_moving_;

    Display& display(uint8_t n) { return display_data_[n % NCHAN]; }
    Button& rec(uint8_t n) { return btn_rec_[n % NCHAN]; }
    Button& solo(uint8_t n) { return btn_solo_[n % NCHAN]; }
    Button& mute(uint8_t n) { return btn_mute_[n % NCHAN]; }
    Button& select(uint8_t n) { return btn_select_[n % NCHAN]; }
    Fader& knob(uint8_t n) { return knobs_[n % NCHAN]; }
    Fader& fader(uint8_t n) { return faders_[n % NCHAN]; }

private:
    Display display_data_[NCHAN];
};

class XTouchExtender : public BaseObject {
    std::vector<Scene> scenes_;
    IntProperty* num_scenes_;
    IntProperty* scene_;
    SymbolEnumProperty* proto_;
    MidiFSMParser parser_;

public:
    XTouchExtender(const PdArgs& args);
    void onFloat(t_float f) override;
    void onAny(t_symbol* s, const AtomListView& l) override;
    void initDone() override;

    void m_vu(t_symbol* s, const AtomListView& lv);
    void m_reset(t_symbol* s, const AtomListView& lv);

    void m_lcd(t_symbol* s, const AtomListView& lv);
    void m_ulcd(t_symbol* s, const AtomListView& lv);
    void m_llcd(t_symbol* s, const AtomListView& lv);
    void m_lcd_align(t_symbol* s, const AtomListView& lv);
    void m_lcd_color(t_symbol* s, const AtomListView& lv);
    void m_lcd_lower(t_symbol* s, const AtomListView& lv);
    void m_lcd_lower_align(t_symbol* s, const AtomListView& lv);
    void m_lcd_mode(t_symbol* s, const AtomListView& lv);
    void m_lcd_upper(t_symbol* s, const AtomListView& lv);
    void m_lcd_upper_align(t_symbol* s, const AtomListView& lv);
    void m_lcd_upper_enum(t_symbol* s, const AtomListView& lv);
    void m_lcd_lower_enum(t_symbol* s, const AtomListView& lv);

    void m_rec(t_symbol* s, const AtomListView& lv);
    void m_solo(t_symbol* s, const AtomListView& lv);
    void m_mute(t_symbol* s, const AtomListView& lv);
    void m_select(t_symbol* s, const AtomListView& lv);
    void m_knob(t_symbol* s, const AtomListView& lv);
    void m_fader(t_symbol* s, const AtomListView& lv);

    void m_rec_get(t_symbol* s, const AtomListView& lv);
    void m_solo_get(t_symbol* s, const AtomListView& lv);
    void m_mute_get(t_symbol* s, const AtomListView& lv);
    void m_select_get(t_symbol* s, const AtomListView& lv);
    void m_knob_get(t_symbol* s, const AtomListView& lv);
    void m_fader_get(t_symbol* s, const AtomListView& lv);

    void m_rec_mode(t_symbol* s, const AtomListView& lv);
    void m_solo_mode(t_symbol* s, const AtomListView& lv);
    void m_mute_mode(t_symbol* s, const AtomListView& lv);
    void m_select_mode(t_symbol* s, const AtomListView& lv);

public:
    Scene& currentScene() { return scenes_[scene_->value()]; }
    Scene& sceneByIdx(uint8_t scene_idx) { return scenes_[scene_idx % scenes_.size()]; }
    Scene& sceneByLogicIdx(uint8_t log_ctl_idx) { return sceneByIdx(log_ctl_idx / Scene::NCHAN); }
    Display& display(int8_t chan) { return sceneByLogicIdx(chan).display(chan % Scene::NCHAN); }

private:
    void m_apply_fn(t_symbol* s, const AtomListView& lv, std::function<void(int, const Atom&)> fn);
    void m_get_button_fn(t_symbol* s, const AtomListView& lv, Button& (Scene::*fn)(uint8_t));
    void m_get_fader_fn(t_symbol* s, const AtomListView& lv, Fader& (Scene::*fn)(uint8_t));

    void parseXMidi();
    void parseHui();
    void parseMcu();

    int msgToIndex(const char* msg);

    void sendVu(uint8_t idx, int db);
    void sendFader(uint8_t scene_idx, uint8_t ctl_idx, t_float v);
    void sendKnob(uint8_t scene_idx, uint8_t ctl_idx, t_float v);
    void sendKnobButton(uint8_t scene_idx, uint8_t ctl_idx, uint8_t v);
    void sendRec(uint8_t scene_idx, uint8_t ctl_idx, int v);
    void sendSolo(uint8_t scene_idx, uint8_t ctl_idx, int v);
    void sendMute(uint8_t scene_idx, uint8_t ctl_idx, int v);
    void sendSelect(uint8_t scene_idx, uint8_t ctl_idx, int v);

    void sendCC(uint8_t cc, uint8_t value, uint8_t ch = 0);
    void sendNote(uint8_t note, uint8_t velocity, uint8_t ch = 0);

    void resetVu();
    void resetFaders();
    void resetKnobs();
    void resetButtons();

    void syncScene();
    void syncDisplay(uint8_t scene_idx, uint8_t ctl_idx);
    void syncLogicDisplay(uint8_t log_idx) { syncDisplay(log_idx / Scene::NCHAN, log_idx % Scene::NCHAN); }

    int numLogicChannels() const { return scenes_.size() * Scene::NCHAN; }
    int numHWChannels() const { return Scene::NCHAN; }

    int getLogicChannel(const AtomListView& lv) const;

    /**
     * @brief calcLogicIdx - calculates logic index for current scene
     * @param idx - hardware control index
     * @return
     */
    uint8_t calcLogicIdx(uint8_t idx) const { return scene_->value() * Scene::NCHAN + idx; }

    void setLogicDisplayUpperText(uint8_t log_idx, const AtomListView& txt);
    void setLogicDisplayLowerText(uint8_t log_idx, const AtomListView& txt);
};

void setup_proto_xtouch_ext();

#endif // HW_XTOUCH_EXT_H
