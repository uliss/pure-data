/* ------------------------------------------------------------
author: "Romain Michon (rmichon@ccrma.stanford.edu)"
copyright: "Romain Michon"
name: "synth.harpsichord"
version: "1.0"
Code generated with Faust 2.30.12 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __synth_harpsichord_H__
#define  __synth_harpsichord_H__

// FAUST Architecture File for ceammc::SoundExternal class
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>

/************************** BEGIN synth_harpsichord_dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class synth_harpsichord_dsp {

    public:

        synth_harpsichord_dsp() {}
        virtual ~synth_harpsichord_dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual synth_harpsichord_dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public synth_harpsichord_dsp {

    protected:

        synth_harpsichord_dsp* fDSP;

    public:

        decorator_dsp(synth_harpsichord_dsp* synth_harpsichord_dsp = nullptr):fDSP(synth_harpsichord_dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual synth_harpsichord_dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/**************************  END  synth_harpsichord_dsp.h **************************/
/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

/**
 The base class of Meta handler to be used in synth_harpsichord_dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN misc.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <string>


using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

static int lsr(int x, int n) { return int(((unsigned int)x) >> n); }

static int int2pow2(int x) { int r = 0; while ((1<<r) < x) r++; return r; }

static long lopt(char* argv[], const char* name, long def)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return std::atoi(argv[i+1]);
    return def;
}

static long lopt1(int argc, char* argv[], const char* longname, const char* shortname, long def)
{
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            return atoi(argv[i]);
        }
    }
    return def;
}

static const char* lopts(char* argv[], const char* name, const char* def)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
    return def;
}

static const char* lopts1(int argc, char* argv[], const char* longname, const char* shortname, const char* def)
{
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            return argv[i];
        }
    }
    return def;
}

static bool isopt(char* argv[], const char* name)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
    return false;
}

static std::string pathToContent(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    std::string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

#endif

/**************************  END  misc.h **************************/

#include "ceammc_faust.h"

using namespace ceammc::faust;

#ifdef FAUST_MACRO
// clang-format off
// clang-format on
#endif

#define sym(name) xsym(name)
#define xsym(name) #name

// clang-format off
#ifndef FAUST_MACRO
struct synth_harpsichord : public synth_harpsichord_dsp {
};
#endif
// clang-format on

#ifdef FAUST_MACRO
// clang-format off
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

/* link with : "" */
#include "harpsichord.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class synth_harpsichordSIG0 {
	
  private:
	
	int iRec17[2];
	
  public:
	
	int getNumInputssynth_harpsichordSIG0() {
		return 0;
	}
	int getNumOutputssynth_harpsichordSIG0() {
		return 1;
	}
	int getInputRatesynth_harpsichordSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRatesynth_harpsichordSIG0(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	void instanceInitsynth_harpsichordSIG0(int sample_rate) {
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			iRec17[l6] = 0;
		}
	}
	
	void fillsynth_harpsichordSIG0(int count, float* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec17[0] = (iRec17[1] + 1);
			table[i] = std::sin((9.58738019e-05f * float((iRec17[0] + -1))));
			iRec17[1] = iRec17[0];
		}
	}

};

static synth_harpsichordSIG0* newsynth_harpsichordSIG0() { return (synth_harpsichordSIG0*)new synth_harpsichordSIG0(); }
static void deletesynth_harpsichordSIG0(synth_harpsichordSIG0* dsp) { delete dsp; }

static float synth_harpsichord_faustpower2_f(float value) {
	return (value * value);
}
static float ftbl0synth_harpsichordSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS synth_harpsichord
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class synth_harpsichord : public synth_harpsichord_dsp {
	
 private:
	
	int fSampleRate;
	float fConst1;
	float fConst4;
	FAUSTFLOAT fHslider0;
	float fConst5;
	float fConst7;
	float fConst8;
	float fRec11[2];
	float fRec10[2];
	int IOTA;
	float fVec0[32768];
	int iConst10;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec12[2];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fCheckbox0;
	float fRec15[2];
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider4;
	float fRec16[2];
	float fConst11;
	FAUSTFLOAT fHslider5;
	float fRec19[2];
	float fRec18[2];
	float fRec25[2];
	float fRec24[2];
	float fRec23[2];
	float fRec22[2];
	float fRec21[2];
	float fRec20[2];
	float fRec31[2];
	float fRec30[2];
	float fRec29[2];
	float fRec28[2];
	float fRec27[2];
	float fRec26[2];
	int iRec33[2];
	float fConst12;
	float fRec34[2];
	float fRec32[2];
	int iRec35[2];
	float fVec1[8192];
	float fConst13;
	float fRec14[3];
	float fConst14;
	float fConst15;
	float fConst16;
	float fConst17;
	float fRec38[2];
	float fRec37[2];
	float fRec36[2];
	float fRec13[8192];
	float fConst18;
	FAUSTFLOAT fHslider6;
	float fVec2[4096];
	int iConst19;
	float fVec3[2048];
	int iConst20;
	float fRec8[2];
	float fConst23;
	float fConst24;
	float fRec42[2];
	float fRec41[2];
	float fVec4[32768];
	int iConst26;
	float fVec5[4096];
	int iConst27;
	float fRec39[2];
	float fConst30;
	float fConst31;
	float fRec46[2];
	float fRec45[2];
	float fVec6[16384];
	int iConst33;
	float fVec7[4096];
	int iConst34;
	float fRec43[2];
	float fConst37;
	float fConst38;
	float fRec50[2];
	float fRec49[2];
	float fVec8[32768];
	int iConst40;
	float fVec9[4096];
	int iConst41;
	float fRec47[2];
	float fConst44;
	float fConst45;
	float fRec54[2];
	float fRec53[2];
	float fVec10[16384];
	int iConst47;
	float fVec11[4096];
	float fVec12[2048];
	int iConst48;
	float fRec51[2];
	float fConst51;
	float fConst52;
	float fRec58[2];
	float fRec57[2];
	float fVec13[16384];
	int iConst54;
	float fVec14[4096];
	int iConst55;
	float fRec55[2];
	float fConst58;
	float fConst59;
	float fRec62[2];
	float fRec61[2];
	float fVec15[16384];
	int iConst61;
	float fVec16[4096];
	int iConst62;
	float fRec59[2];
	float fConst65;
	float fConst66;
	float fRec66[2];
	float fRec65[2];
	float fVec17[16384];
	int iConst68;
	float fVec18[2048];
	int iConst69;
	float fRec63[2];
	float fRec0[3];
	float fRec1[3];
	float fRec2[3];
	float fRec3[3];
	float fRec4[3];
	float fRec5[3];
	float fRec6[3];
	float fRec7[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.1");
		m->declare("author", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("ceammc.lib/name", "Ceammc PureData misc utils");
		m->declare("ceammc.lib/version", "0.1.2");
		m->declare("ceammc_instruments.lib/name", "CEAMMC replacement for intruments.lib");
		m->declare("ceammc_instruments.lib/version", "0.3");
		m->declare("ceammc_ui.lib/name", "CEAMMC faust default UI elements");
		m->declare("ceammc_ui.lib/version", "0.1.2");
		m->declare("compile_options", "-lang cpp -es 1 -scal -ftz 0");
		m->declare("compressors.lib/compression_gain_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compression_gain_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compression_gain_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_lad_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_lad_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_lad_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/compressor_mono:author", "Julius O. Smith III");
		m->declare("compressors.lib/compressor_mono:copyright", "Copyright (C) 2014-2020 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("compressors.lib/compressor_mono:license", "MIT-style STK-4.3 license");
		m->declare("compressors.lib/name", "Faust Compressor Effect Library");
		m->declare("compressors.lib/version", "0.1");
		m->declare("copyright", "Romain Michon");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("description", "Nonlinear WaveGuide Commuted Harpsichord");
		m->declare("filename", "synth_harpsichord.dsp");
		m->declare("filters.lib/allpass_comb:author", "Julius O. Smith III");
		m->declare("filters.lib/allpass_comb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpass_comb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/allpassnn:author", "Julius O. Smith III");
		m->declare("filters.lib/allpassnn:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/allpassnn:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("instruments.lib/author", "Romain Michon (rmichon@ccrma.stanford.edu)");
		m->declare("instruments.lib/copyright", "Romain Michon");
		m->declare("instruments.lib/licence", "STK-4.3");
		m->declare("instruments.lib/name", "Faust-STK Tools Library");
		m->declare("instruments.lib/version", "1.0");
		m->declare("licence", "STK-4.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "synth.harpsichord");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("reverbs.lib/name", "Faust Reverb Library");
		m->declare("reverbs.lib/version", "0.0");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.2");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("spn.lib/name", "Standart Pitch Notation constants");
		m->declare("spn.lib/version", "0.2");
		m->declare("version", "1.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
		synth_harpsichordSIG0* sig0 = newsynth_harpsichordSIG0();
		sig0->instanceInitsynth_harpsichordSIG0(sample_rate);
		sig0->fillsynth_harpsichordSIG0(65536, ftbl0synth_harpsichordSIG0);
		deletesynth_harpsichordSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = std::cos((37699.1133f / fConst0));
		float fConst2 = std::floor(((0.219990999f * fConst0) + 0.5f));
		float fConst3 = ((0.0f - (6.90775537f * fConst2)) / fConst0);
		fConst4 = (0.25f * fConst3);
		fConst5 = (0.166666672f * fConst3);
		float fConst6 = (1.0f / std::tan((628.318542f / fConst0)));
		fConst7 = (1.0f / (fConst6 + 1.0f));
		fConst8 = (1.0f - fConst6);
		float fConst9 = std::floor(((0.0191229992f * fConst0) + 0.5f));
		iConst10 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst2 - fConst9))));
		fConst11 = (1.0f / fConst0);
		fConst12 = (7.0f / fConst0);
		fConst13 = (0.0022727272f * fConst0);
		fConst14 = std::exp((0.0f - (0.200000003f / fConst0)));
		fConst15 = (1.0f - fConst14);
		fConst16 = std::exp((0.0f - (0.100000001f / fConst0)));
		fConst17 = std::exp((0.0f - (0.0199999996f / fConst0)));
		fConst18 = (0.0011363636f * fConst0);
		iConst19 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (0.0199999996f * fConst0))));
		iConst20 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst9 + -1.0f))));
		float fConst21 = std::floor(((0.256891012f * fConst0) + 0.5f));
		float fConst22 = ((0.0f - (6.90775537f * fConst21)) / fConst0);
		fConst23 = (0.25f * fConst22);
		fConst24 = (0.166666672f * fConst22);
		float fConst25 = std::floor(((0.0273330007f * fConst0) + 0.5f));
		iConst26 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst21 - fConst25))));
		iConst27 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst25 + -1.0f))));
		float fConst28 = std::floor(((0.192303002f * fConst0) + 0.5f));
		float fConst29 = ((0.0f - (6.90775537f * fConst28)) / fConst0);
		fConst30 = (0.25f * fConst29);
		fConst31 = (0.166666672f * fConst29);
		float fConst32 = std::floor(((0.0292910002f * fConst0) + 0.5f));
		iConst33 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst28 - fConst32))));
		iConst34 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst32 + -1.0f))));
		float fConst35 = std::floor(((0.210389003f * fConst0) + 0.5f));
		float fConst36 = ((0.0f - (6.90775537f * fConst35)) / fConst0);
		fConst37 = (0.25f * fConst36);
		fConst38 = (0.166666672f * fConst36);
		float fConst39 = std::floor(((0.0244210009f * fConst0) + 0.5f));
		iConst40 = int(std::min<float>(16384.0f, std::max<float>(0.0f, (fConst35 - fConst39))));
		iConst41 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst39 + -1.0f))));
		float fConst42 = std::floor(((0.125f * fConst0) + 0.5f));
		float fConst43 = ((0.0f - (6.90775537f * fConst42)) / fConst0);
		fConst44 = (0.25f * fConst43);
		fConst45 = (0.166666672f * fConst43);
		float fConst46 = std::floor(((0.0134579996f * fConst0) + 0.5f));
		iConst47 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst42 - fConst46))));
		iConst48 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst46 + -1.0f))));
		float fConst49 = std::floor(((0.127837002f * fConst0) + 0.5f));
		float fConst50 = ((0.0f - (6.90775537f * fConst49)) / fConst0);
		fConst51 = (0.25f * fConst50);
		fConst52 = (0.166666672f * fConst50);
		float fConst53 = std::floor(((0.0316039994f * fConst0) + 0.5f));
		iConst54 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst49 - fConst53))));
		iConst55 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst53 + -1.0f))));
		float fConst56 = std::floor(((0.174713001f * fConst0) + 0.5f));
		float fConst57 = ((0.0f - (6.90775537f * fConst56)) / fConst0);
		fConst58 = (0.25f * fConst57);
		fConst59 = (0.166666672f * fConst57);
		float fConst60 = std::floor(((0.0229039993f * fConst0) + 0.5f));
		iConst61 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst56 - fConst60))));
		iConst62 = int(std::min<float>(2048.0f, std::max<float>(0.0f, (fConst60 + -1.0f))));
		float fConst63 = std::floor(((0.153128996f * fConst0) + 0.5f));
		float fConst64 = ((0.0f - (6.90775537f * fConst63)) / fConst0);
		fConst65 = (0.25f * fConst64);
		fConst66 = (0.166666672f * fConst64);
		float fConst67 = std::floor(((0.0203460008f * fConst0) + 0.5f));
		iConst68 = int(std::min<float>(8192.0f, std::max<float>(0.0f, (fConst63 - fConst67))));
		iConst69 = int(std::min<float>(1024.0f, std::max<float>(0.0f, (fConst67 + -1.0f))));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.35999999999999999f);
		fHslider1 = FAUSTFLOAT(0.59999999999999998f);
		fHslider2 = FAUSTFLOAT(0.13700000000000001f);
		fHslider3 = FAUSTFLOAT(48.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(220.0f);
		fHslider6 = FAUSTFLOAT(0.5f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec11[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec10[l1] = 0.0f;
		}
		IOTA = 0;
		for (int l2 = 0; (l2 < 32768); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec12[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec15[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec16[l5] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec19[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec18[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec25[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec24[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec23[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec22[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec21[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec20[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec31[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec30[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec29[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec28[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec27[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec26[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			iRec33[l21] = 0;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec34[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec32[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			iRec35[l24] = 0;
		}
		for (int l25 = 0; (l25 < 8192); l25 = (l25 + 1)) {
			fVec1[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec14[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec38[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec37[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec36[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 8192); l30 = (l30 + 1)) {
			fRec13[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 4096); l31 = (l31 + 1)) {
			fVec2[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 2048); l32 = (l32 + 1)) {
			fVec3[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec8[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec42[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec41[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 32768); l36 = (l36 + 1)) {
			fVec4[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 4096); l37 = (l37 + 1)) {
			fVec5[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec39[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec46[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec45[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 16384); l41 = (l41 + 1)) {
			fVec6[l41] = 0.0f;
		}
		for (int l42 = 0; (l42 < 4096); l42 = (l42 + 1)) {
			fVec7[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec43[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec50[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec49[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 32768); l46 = (l46 + 1)) {
			fVec8[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 4096); l47 = (l47 + 1)) {
			fVec9[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec47[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec54[l49] = 0.0f;
		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec53[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 16384); l51 = (l51 + 1)) {
			fVec10[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 4096); l52 = (l52 + 1)) {
			fVec11[l52] = 0.0f;
		}
		for (int l53 = 0; (l53 < 2048); l53 = (l53 + 1)) {
			fVec12[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec51[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec58[l55] = 0.0f;
		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec57[l56] = 0.0f;
		}
		for (int l57 = 0; (l57 < 16384); l57 = (l57 + 1)) {
			fVec13[l57] = 0.0f;
		}
		for (int l58 = 0; (l58 < 4096); l58 = (l58 + 1)) {
			fVec14[l58] = 0.0f;
		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec55[l59] = 0.0f;
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec62[l60] = 0.0f;
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec61[l61] = 0.0f;
		}
		for (int l62 = 0; (l62 < 16384); l62 = (l62 + 1)) {
			fVec15[l62] = 0.0f;
		}
		for (int l63 = 0; (l63 < 4096); l63 = (l63 + 1)) {
			fVec16[l63] = 0.0f;
		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec59[l64] = 0.0f;
		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec66[l65] = 0.0f;
		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec65[l66] = 0.0f;
		}
		for (int l67 = 0; (l67 < 16384); l67 = (l67 + 1)) {
			fVec17[l67] = 0.0f;
		}
		for (int l68 = 0; (l68 < 2048); l68 = (l68 + 1)) {
			fVec18[l68] = 0.0f;
		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec63[l69] = 0.0f;
		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec0[l70] = 0.0f;
		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec1[l71] = 0.0f;
		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec2[l72] = 0.0f;
		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec3[l73] = 0.0f;
		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec4[l74] = 0.0f;
		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec5[l75] = 0.0f;
		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec6[l76] = 0.0f;
		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec7[l77] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual synth_harpsichord* clone() {
		return new synth_harpsichord();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("synth.harpsichord");
		ui_interface->declare(&fCheckbox0, "type", "float");
		ui_interface->addCheckButton("gate", &fCheckbox0);
		ui_interface->declare(&fHslider5, "tooltip", "Frequency of the sine wave for the modulation of theta (works if Modulation Type=3)");
		ui_interface->declare(&fHslider5, "unit", "Hz");
		ui_interface->addHorizontalSlider("modfreq", &fHslider5, 220.0f, 20.0f, 1000.0f, 0.100000001f);
		ui_interface->declare(&fEntry0, "tooltip", "0=theta is modulated by the incoming signal; 1=theta is modulated by the averaged incoming signal; 2=theta is modulated by the squared incoming signal; 3=theta is modulated by a sine wave of frequency freqMod; 4=theta is modulated by a sine wave of frequency freq;");
		ui_interface->declare(&fEntry0, "type", "int");
		ui_interface->addNumEntry("modtype", &fEntry0, 0.0f, 0.0f, 4.0f, 1.0f);
		ui_interface->declare(&fHslider4, "tooltip", "Nonlinearity factor (value between 0 and 1)");
		ui_interface->addHorizontalSlider("nonlin", &fHslider4, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("pan", &fHslider1, 0.600000024f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("pitch", &fHslider3, 48.0f, 12.0f, 96.0f, 0.00100000005f);
		ui_interface->addHorizontalSlider("reverb_gain", &fHslider2, 0.136999995f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("room_size", &fHslider0, 0.360000014f, 0.00499999989f, 1.0f, 0.00999999978f);
		ui_interface->addHorizontalSlider("width", &fHslider6, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = float(fHslider0);
		float fSlow1 = std::exp((fConst4 / fSlow0));
		float fSlow2 = synth_harpsichord_faustpower2_f(fSlow1);
		float fSlow3 = (1.0f - (fConst1 * fSlow2));
		float fSlow4 = (1.0f - fSlow2);
		float fSlow5 = (fSlow3 / fSlow4);
		float fSlow6 = std::sqrt(std::max<float>(0.0f, ((synth_harpsichord_faustpower2_f(fSlow3) / synth_harpsichord_faustpower2_f(fSlow4)) + -1.0f)));
		float fSlow7 = (fSlow5 - fSlow6);
		float fSlow8 = (fSlow1 * (fSlow6 + (1.0f - fSlow5)));
		float fSlow9 = ((std::exp((fConst5 / fSlow0)) / fSlow1) + -1.0f);
		float fSlow10 = float(fHslider1);
		float fSlow11 = (4.0f * fSlow10);
		float fSlow12 = (0.00100000005f * float(fHslider2));
		float fSlow13 = std::pow(2.0f, (0.0833333358f * (float(fHslider3) + -69.0f)));
		float fSlow14 = (440.0f * fSlow13);
		float fSlow15 = float(getValueLoopFilterb0(float(fSlow14)));
		float fSlow16 = float(fCheckbox0);
		int iSlow17 = (fSlow16 > 0.0f);
		int iSlow18 = (iSlow17 < 1);
		float fSlow19 = (0.00100000005f * ((0.999599993f * float(iSlow17)) + (0.899999976f * (float(iSlow18) * float(getValueReleaseLoopGain(float(fSlow14)))))));
		int iSlow20 = int(float(fEntry0));
		float fSlow21 = float((iSlow20 >= 3));
		float fSlow22 = (0.00100000005f * float(fHslider4));
		float fSlow23 = (440.0f * (fSlow13 * float((iSlow20 == 4))));
		float fSlow24 = float((iSlow20 != 4));
		float fSlow25 = (0.00100000005f * float(fHslider5));
		float fSlow26 = float((iSlow20 < 3));
		float fSlow27 = (3.14159274f * float((iSlow20 == 0)));
		float fSlow28 = (1.57079637f * float((iSlow20 == 1)));
		float fSlow29 = (3.14159274f * float((iSlow20 == 2)));
		int iSlow30 = (iSlow17 > 0);
		float fSlow31 = (fConst12 / float(getValueDryTapAmpT60(float(fSlow14))));
		float fSlow32 = (0.00100000005f * std::min<float>(1.0f, std::max<float>(0.0f, fSlow16)));
		int iSlow33 = int(std::min<float>(4096.0f, std::max<float>(0.0f, (fConst13 / fSlow13))));
		float fSlow34 = float(getValueLoopFiltera1(float(fSlow14)));
		float fSlow35 = float(getValueLoopFiltera2(float(fSlow14)));
		float fSlow36 = float(getValueLoopFilterb1(float(fSlow14)));
		float fSlow37 = float(getValueLoopFilterb2(float(fSlow14)));
		int iSlow38 = int(std::min<float>(4096.0f, std::max<float>(0.0f, (fConst18 * (float(fHslider6) / fSlow13)))));
		float fSlow39 = std::exp((fConst23 / fSlow0));
		float fSlow40 = synth_harpsichord_faustpower2_f(fSlow39);
		float fSlow41 = (1.0f - (fConst1 * fSlow40));
		float fSlow42 = (1.0f - fSlow40);
		float fSlow43 = (fSlow41 / fSlow42);
		float fSlow44 = std::sqrt(std::max<float>(0.0f, ((synth_harpsichord_faustpower2_f(fSlow41) / synth_harpsichord_faustpower2_f(fSlow42)) + -1.0f)));
		float fSlow45 = (fSlow43 - fSlow44);
		float fSlow46 = (fSlow39 * (fSlow44 + (1.0f - fSlow43)));
		float fSlow47 = ((std::exp((fConst24 / fSlow0)) / fSlow39) + -1.0f);
		float fSlow48 = std::exp((fConst30 / fSlow0));
		float fSlow49 = synth_harpsichord_faustpower2_f(fSlow48);
		float fSlow50 = (1.0f - (fConst1 * fSlow49));
		float fSlow51 = (1.0f - fSlow49);
		float fSlow52 = (fSlow50 / fSlow51);
		float fSlow53 = std::sqrt(std::max<float>(0.0f, ((synth_harpsichord_faustpower2_f(fSlow50) / synth_harpsichord_faustpower2_f(fSlow51)) + -1.0f)));
		float fSlow54 = (fSlow52 - fSlow53);
		float fSlow55 = (fSlow48 * (fSlow53 + (1.0f - fSlow52)));
		float fSlow56 = ((std::exp((fConst31 / fSlow0)) / fSlow48) + -1.0f);
		float fSlow57 = std::exp((fConst37 / fSlow0));
		float fSlow58 = synth_harpsichord_faustpower2_f(fSlow57);
		float fSlow59 = (1.0f - (fConst1 * fSlow58));
		float fSlow60 = (1.0f - fSlow58);
		float fSlow61 = (fSlow59 / fSlow60);
		float fSlow62 = std::sqrt(std::max<float>(0.0f, ((synth_harpsichord_faustpower2_f(fSlow59) / synth_harpsichord_faustpower2_f(fSlow60)) + -1.0f)));
		float fSlow63 = (fSlow61 - fSlow62);
		float fSlow64 = (fSlow57 * (fSlow62 + (1.0f - fSlow61)));
		float fSlow65 = ((std::exp((fConst38 / fSlow0)) / fSlow57) + -1.0f);
		float fSlow66 = std::exp((fConst44 / fSlow0));
		float fSlow67 = synth_harpsichord_faustpower2_f(fSlow66);
		float fSlow68 = (1.0f - (fConst1 * fSlow67));
		float fSlow69 = (1.0f - fSlow67);
		float fSlow70 = (fSlow68 / fSlow69);
		float fSlow71 = std::sqrt(std::max<float>(0.0f, ((synth_harpsichord_faustpower2_f(fSlow68) / synth_harpsichord_faustpower2_f(fSlow69)) + -1.0f)));
		float fSlow72 = (fSlow70 - fSlow71);
		float fSlow73 = (fSlow66 * (fSlow71 + (1.0f - fSlow70)));
		float fSlow74 = ((std::exp((fConst45 / fSlow0)) / fSlow66) + -1.0f);
		float fSlow75 = (4.0f * (1.0f - fSlow10));
		float fSlow76 = std::exp((fConst51 / fSlow0));
		float fSlow77 = synth_harpsichord_faustpower2_f(fSlow76);
		float fSlow78 = (1.0f - (fConst1 * fSlow77));
		float fSlow79 = (1.0f - fSlow77);
		float fSlow80 = (fSlow78 / fSlow79);
		float fSlow81 = std::sqrt(std::max<float>(0.0f, ((synth_harpsichord_faustpower2_f(fSlow78) / synth_harpsichord_faustpower2_f(fSlow79)) + -1.0f)));
		float fSlow82 = (fSlow80 - fSlow81);
		float fSlow83 = (fSlow76 * (fSlow81 + (1.0f - fSlow80)));
		float fSlow84 = ((std::exp((fConst52 / fSlow0)) / fSlow76) + -1.0f);
		float fSlow85 = std::exp((fConst58 / fSlow0));
		float fSlow86 = synth_harpsichord_faustpower2_f(fSlow85);
		float fSlow87 = (1.0f - (fConst1 * fSlow86));
		float fSlow88 = (1.0f - fSlow86);
		float fSlow89 = (fSlow87 / fSlow88);
		float fSlow90 = std::sqrt(std::max<float>(0.0f, ((synth_harpsichord_faustpower2_f(fSlow87) / synth_harpsichord_faustpower2_f(fSlow88)) + -1.0f)));
		float fSlow91 = (fSlow89 - fSlow90);
		float fSlow92 = (fSlow85 * (fSlow90 + (1.0f - fSlow89)));
		float fSlow93 = ((std::exp((fConst59 / fSlow0)) / fSlow85) + -1.0f);
		float fSlow94 = std::exp((fConst65 / fSlow0));
		float fSlow95 = synth_harpsichord_faustpower2_f(fSlow94);
		float fSlow96 = (1.0f - (fConst1 * fSlow95));
		float fSlow97 = (1.0f - fSlow95);
		float fSlow98 = (fSlow96 / fSlow97);
		float fSlow99 = std::sqrt(std::max<float>(0.0f, ((synth_harpsichord_faustpower2_f(fSlow96) / synth_harpsichord_faustpower2_f(fSlow97)) + -1.0f)));
		float fSlow100 = (fSlow98 - fSlow99);
		float fSlow101 = (fSlow94 * (fSlow99 + (1.0f - fSlow98)));
		float fSlow102 = ((std::exp((fConst66 / fSlow0)) / fSlow94) + -1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec11[0] = (0.0f - (fConst7 * ((fConst8 * fRec11[1]) - (fRec7[1] + fRec7[2]))));
			fRec10[0] = ((fSlow7 * fRec10[1]) + (fSlow8 * (fRec7[1] + (fSlow9 * fRec11[0]))));
			fVec0[(IOTA & 32767)] = ((0.353553385f * fRec10[0]) + 9.99999968e-21f);
			fRec12[0] = (fSlow12 + (0.999000013f * fRec12[1]));
			fRec15[0] = (fSlow19 + (0.999000013f * fRec15[1]));
			float fTemp0 = fRec13[((IOTA - 1) & 8191)];
			fRec16[0] = (fSlow22 + (0.999000013f * fRec16[1]));
			fRec19[0] = (fSlow25 + (0.999000013f * fRec19[1]));
			float fTemp1 = (fRec18[1] + (fConst11 * (fSlow23 + (fSlow24 * fRec19[0]))));
			fRec18[0] = (fTemp1 - std::floor(fTemp1));
			float fTemp2 = (3.14159274f * (fRec16[0] * ftbl0synth_harpsichordSIG0[int((65536.0f * fRec18[0]))]));
			float fTemp3 = std::sin(fTemp2);
			float fTemp4 = std::cos(fTemp2);
			float fTemp5 = ((fTemp0 * fTemp4) - (fTemp3 * fRec20[1]));
			float fTemp6 = ((fTemp4 * fTemp5) - (fTemp3 * fRec21[1]));
			float fTemp7 = ((fTemp4 * fTemp6) - (fTemp3 * fRec22[1]));
			float fTemp8 = ((fTemp4 * fTemp7) - (fTemp3 * fRec23[1]));
			float fTemp9 = ((fTemp4 * fTemp8) - (fTemp3 * fRec24[1]));
			fRec25[0] = ((fTemp4 * fTemp9) - (fTemp3 * fRec25[1]));
			fRec24[0] = ((fTemp3 * fTemp9) + (fTemp4 * fRec25[1]));
			fRec23[0] = ((fTemp3 * fTemp8) + (fTemp4 * fRec24[1]));
			fRec22[0] = ((fTemp3 * fTemp7) + (fTemp4 * fRec23[1]));
			fRec21[0] = ((fTemp3 * fTemp6) + (fTemp4 * fRec22[1]));
			fRec20[0] = ((fTemp3 * fTemp5) + (fTemp4 * fRec21[1]));
			float fTemp10 = (fRec16[0] * (((fSlow27 * fTemp0) + (fSlow28 * (fTemp0 + fRec13[((IOTA - 2) & 8191)]))) + (fSlow29 * synth_harpsichord_faustpower2_f(fTemp0))));
			float fTemp11 = std::sin(fTemp10);
			float fTemp12 = std::cos(fTemp10);
			float fTemp13 = ((fTemp0 * fTemp12) - (fTemp11 * fRec26[1]));
			float fTemp14 = ((fTemp12 * fTemp13) - (fTemp11 * fRec27[1]));
			float fTemp15 = ((fTemp12 * fTemp14) - (fTemp11 * fRec28[1]));
			float fTemp16 = ((fTemp12 * fTemp15) - (fTemp11 * fRec29[1]));
			float fTemp17 = ((fTemp12 * fTemp16) - (fTemp11 * fRec30[1]));
			fRec31[0] = ((fTemp12 * fTemp17) - (fTemp11 * fRec31[1]));
			fRec30[0] = ((fTemp11 * fTemp17) + (fTemp12 * fRec31[1]));
			fRec29[0] = ((fTemp11 * fTemp16) + (fTemp12 * fRec30[1]));
			fRec28[0] = ((fTemp11 * fTemp15) + (fTemp12 * fRec29[1]));
			fRec27[0] = ((fTemp11 * fTemp14) + (fTemp12 * fRec28[1]));
			fRec26[0] = ((fTemp11 * fTemp13) + (fTemp12 * fRec27[1]));
			iRec33[0] = ((iSlow17 * iRec33[1]) + 1);
			float fTemp18 = float((iRec33[0] + -1));
			float fTemp19 = float(((fTemp18 < 2.0f) & iSlow30));
			fRec34[0] = (fSlow32 + (0.999000013f * fRec34[1]));
			float fTemp20 = ((0.0301973838f * fTemp19) + (float(((fTemp18 >= 2.0f) | iSlow18)) * std::exp((0.0f - (fSlow31 / fRec34[0])))));
			fRec32[0] = ((fRec32[1] * fTemp20) + (0.150000006f * (fTemp19 * (1.0f - fTemp20))));
			iRec35[0] = ((1103515245 * iRec35[1]) + 12345);
			fVec1[(IOTA & 8191)] = ((fRec15[0] * ((fSlow21 * ((fTemp0 * fTemp3) + (fRec20[1] * fTemp4))) + (fSlow26 * ((fRec16[0] * ((fTemp0 * fTemp11) + (fRec26[1] * fTemp12))) + ((1.0f - fRec16[0]) * fTemp0))))) + (4.65661287e-10f * (fRec32[0] * float(iRec35[0]))));
			fRec14[0] = (fVec1[((IOTA - iSlow33) & 8191)] - ((fSlow34 * fRec14[1]) + (fSlow35 * fRec14[2])));
			float fTemp21 = (((fSlow15 * fRec14[0]) + (fSlow36 * fRec14[1])) + (fSlow37 * fRec14[2]));
			float fTemp22 = std::fabs(fTemp21);
			float fTemp23 = ((fRec37[1] > fTemp22) ? fConst17 : fConst16);
			fRec38[0] = ((fRec38[1] * fTemp23) + (fTemp22 * (1.0f - fTemp23)));
			fRec37[0] = fRec38[0];
			fRec36[0] = ((fConst14 * fRec36[1]) + (fConst15 * (0.0f - (0.5f * std::max<float>(((20.0f * std::log10(fRec37[0])) + -100.0f), 0.0f)))));
			fRec13[(IOTA & 8191)] = (fTemp21 * std::pow(10.0f, (0.0500000007f * fRec36[0])));
			float fTemp24 = fRec13[((IOTA - iSlow38) & 8191)];
			fVec2[(IOTA & 4095)] = (fSlow11 * (fRec12[0] * fTemp24));
			float fTemp25 = (0.300000012f * fVec2[((IOTA - iConst19) & 4095)]);
			float fTemp26 = (((0.600000024f * fRec8[1]) + fVec0[((IOTA - iConst10) & 32767)]) - fTemp25);
			fVec3[(IOTA & 2047)] = fTemp26;
			fRec8[0] = fVec3[((IOTA - iConst20) & 2047)];
			float fRec9 = (0.0f - (0.600000024f * fTemp26));
			fRec42[0] = (0.0f - (fConst7 * ((fConst8 * fRec42[1]) - (fRec3[1] + fRec3[2]))));
			fRec41[0] = ((fSlow45 * fRec41[1]) + (fSlow46 * (fRec3[1] + (fSlow47 * fRec42[0]))));
			fVec4[(IOTA & 32767)] = ((0.353553385f * fRec41[0]) + 9.99999968e-21f);
			float fTemp27 = (((0.600000024f * fRec39[1]) + fVec4[((IOTA - iConst26) & 32767)]) - fTemp25);
			fVec5[(IOTA & 4095)] = fTemp27;
			fRec39[0] = fVec5[((IOTA - iConst27) & 4095)];
			float fRec40 = (0.0f - (0.600000024f * fTemp27));
			fRec46[0] = (0.0f - (fConst7 * ((fConst8 * fRec46[1]) - (fRec5[1] + fRec5[2]))));
			fRec45[0] = ((fSlow54 * fRec45[1]) + (fSlow55 * (fRec5[1] + (fSlow56 * fRec46[0]))));
			fVec6[(IOTA & 16383)] = ((0.353553385f * fRec45[0]) + 9.99999968e-21f);
			float fTemp28 = (fVec6[((IOTA - iConst33) & 16383)] + (fTemp25 + (0.600000024f * fRec43[1])));
			fVec7[(IOTA & 4095)] = fTemp28;
			fRec43[0] = fVec7[((IOTA - iConst34) & 4095)];
			float fRec44 = (0.0f - (0.600000024f * fTemp28));
			fRec50[0] = (0.0f - (fConst7 * ((fConst8 * fRec50[1]) - (fRec1[1] + fRec1[2]))));
			fRec49[0] = ((fSlow63 * fRec49[1]) + (fSlow64 * (fRec1[1] + (fSlow65 * fRec50[0]))));
			fVec8[(IOTA & 32767)] = ((0.353553385f * fRec49[0]) + 9.99999968e-21f);
			float fTemp29 = (fTemp25 + ((0.600000024f * fRec47[1]) + fVec8[((IOTA - iConst40) & 32767)]));
			fVec9[(IOTA & 4095)] = fTemp29;
			fRec47[0] = fVec9[((IOTA - iConst41) & 4095)];
			float fRec48 = (0.0f - (0.600000024f * fTemp29));
			fRec54[0] = (0.0f - (fConst7 * ((fConst8 * fRec54[1]) - (fRec6[1] + fRec6[2]))));
			fRec53[0] = ((fSlow72 * fRec53[1]) + (fSlow73 * (fRec6[1] + (fSlow74 * fRec54[0]))));
			fVec10[(IOTA & 16383)] = ((0.353553385f * fRec53[0]) + 9.99999968e-21f);
			float fTemp30 = fRec13[((IOTA - 0) & 8191)];
			fVec11[(IOTA & 4095)] = (fSlow75 * (fTemp30 * fRec12[0]));
			float fTemp31 = (0.300000012f * fVec11[((IOTA - iConst19) & 4095)]);
			float fTemp32 = (fVec10[((IOTA - iConst47) & 16383)] - (fTemp31 + (0.600000024f * fRec51[1])));
			fVec12[(IOTA & 2047)] = fTemp32;
			fRec51[0] = fVec12[((IOTA - iConst48) & 2047)];
			float fRec52 = (0.600000024f * fTemp32);
			fRec58[0] = (0.0f - (fConst7 * ((fConst8 * fRec58[1]) - (fRec2[1] + fRec2[2]))));
			fRec57[0] = ((fSlow82 * fRec57[1]) + (fSlow83 * (fRec2[1] + (fSlow84 * fRec58[0]))));
			fVec13[(IOTA & 16383)] = ((0.353553385f * fRec57[0]) + 9.99999968e-21f);
			float fTemp33 = (fVec13[((IOTA - iConst54) & 16383)] - (fTemp31 + (0.600000024f * fRec55[1])));
			fVec14[(IOTA & 4095)] = fTemp33;
			fRec55[0] = fVec14[((IOTA - iConst55) & 4095)];
			float fRec56 = (0.600000024f * fTemp33);
			fRec62[0] = (0.0f - (fConst7 * ((fConst8 * fRec62[1]) - (fRec4[1] + fRec4[2]))));
			fRec61[0] = ((fSlow91 * fRec61[1]) + (fSlow92 * (fRec4[1] + (fSlow93 * fRec62[0]))));
			fVec15[(IOTA & 16383)] = ((0.353553385f * fRec61[0]) + 9.99999968e-21f);
			float fTemp34 = ((fTemp31 + fVec15[((IOTA - iConst61) & 16383)]) - (0.600000024f * fRec59[1]));
			fVec16[(IOTA & 4095)] = fTemp34;
			fRec59[0] = fVec16[((IOTA - iConst62) & 4095)];
			float fRec60 = (0.600000024f * fTemp34);
			fRec66[0] = (0.0f - (fConst7 * ((fConst8 * fRec66[1]) - (fRec0[1] + fRec0[2]))));
			fRec65[0] = ((fSlow100 * fRec65[1]) + (fSlow101 * (fRec0[1] + (fSlow102 * fRec66[0]))));
			fVec17[(IOTA & 16383)] = ((0.353553385f * fRec65[0]) + 9.99999968e-21f);
			float fTemp35 = ((fVec17[((IOTA - iConst68) & 16383)] + fTemp31) - (0.600000024f * fRec63[1]));
			fVec18[(IOTA & 2047)] = fTemp35;
			fRec63[0] = fVec18[((IOTA - iConst69) & 2047)];
			float fRec64 = (0.600000024f * fTemp35);
			float fTemp36 = (fRec59[1] + fRec55[1]);
			float fTemp37 = (fRec52 + (fRec56 + (fRec60 + (fRec64 + (fRec63[1] + fTemp36)))));
			fRec0[0] = (fRec8[1] + (fRec39[1] + (fRec43[1] + (fRec47[1] + (fRec51[1] + (fRec9 + (fRec40 + (fRec44 + (fRec48 + fTemp37)))))))));
			fRec1[0] = ((fRec51[1] + fTemp37) - (fRec8[1] + (fRec39[1] + (fRec43[1] + (fRec47[1] + (fRec9 + (fRec40 + (fRec48 + fRec44))))))));
			float fTemp38 = (fRec60 + (fRec64 + (fRec63[1] + fRec59[1])));
			float fTemp39 = (fRec52 + (fRec56 + fRec55[1]));
			fRec2[0] = ((fRec43[1] + (fRec47[1] + (fRec44 + (fRec48 + fTemp38)))) - (fRec8[1] + (fRec39[1] + (fRec51[1] + (fRec9 + (fRec40 + fTemp39))))));
			fRec3[0] = ((fRec8[1] + (fRec39[1] + (fRec9 + (fRec40 + fTemp38)))) - (fRec43[1] + (fRec47[1] + (fRec51[1] + (fRec44 + (fRec48 + fTemp39))))));
			float fTemp40 = (fRec56 + (fRec64 + (fRec63[1] + fRec55[1])));
			float fTemp41 = (fRec52 + (fRec60 + fRec59[1]));
			fRec4[0] = ((fRec39[1] + (fRec47[1] + (fRec40 + (fRec48 + fTemp40)))) - (fRec8[1] + (fRec43[1] + (fRec51[1] + (fRec9 + (fRec44 + fTemp41))))));
			fRec5[0] = ((fRec8[1] + (fRec43[1] + (fRec9 + (fRec44 + fTemp40)))) - (fRec39[1] + (fRec47[1] + (fRec51[1] + (fRec40 + (fRec48 + fTemp41))))));
			float fTemp42 = (fRec52 + (fRec64 + fRec63[1]));
			float fTemp43 = (fRec56 + (fRec60 + fTemp36));
			fRec6[0] = ((fRec8[1] + (fRec47[1] + (fRec51[1] + (fRec9 + (fRec48 + fTemp42))))) - (fRec39[1] + (fRec43[1] + (fRec40 + (fRec44 + fTemp43)))));
			fRec7[0] = ((fRec39[1] + (fRec43[1] + (fRec51[1] + (fRec40 + (fRec44 + fTemp42))))) - (fRec8[1] + (fRec47[1] + (fRec9 + (fRec48 + fTemp43)))));
			float fTemp44 = (1.0f - fRec12[0]);
			output0[i] = FAUSTFLOAT(((0.370000005f * (fRec1[0] + fRec2[0])) + (fSlow75 * (fTemp30 * fTemp44))));
			output1[i] = FAUSTFLOAT(((0.370000005f * (fRec1[0] - fRec2[0])) + (fSlow11 * (fTemp44 * fTemp24))));
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			IOTA = (IOTA + 1);
			fRec12[1] = fRec12[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			iRec33[1] = iRec33[0];
			fRec34[1] = fRec34[0];
			fRec32[1] = fRec32[0];
			iRec35[1] = iRec35[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec8[1] = fRec8[0];
			fRec42[1] = fRec42[0];
			fRec41[1] = fRec41[0];
			fRec39[1] = fRec39[0];
			fRec46[1] = fRec46[0];
			fRec45[1] = fRec45[0];
			fRec43[1] = fRec43[0];
			fRec50[1] = fRec50[0];
			fRec49[1] = fRec49[0];
			fRec47[1] = fRec47[0];
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			fRec51[1] = fRec51[0];
			fRec58[1] = fRec58[0];
			fRec57[1] = fRec57[0];
			fRec55[1] = fRec55[0];
			fRec62[1] = fRec62[0];
			fRec61[1] = fRec61[0];
			fRec59[1] = fRec59[0];
			fRec66[1] = fRec66[0];
			fRec65[1] = fRec65[0];
			fRec63[1] = fRec63[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
		}
	}

};
// clang-format on
#endif

    template <class T>
    struct _synth_harpsichord_UI : public UI {
    static std::string name;
};

template <class T>
std::string _synth_harpsichord_UI<T>::name(sym(synth_harpsichord));

typedef _synth_harpsichord_UI<synth_harpsichord> synth_harpsichord_UI;

class faust_synth_harpsichord_tilde : public FaustExternal<synth_harpsichord, synth_harpsichord_UI> {
public:
    faust_synth_harpsichord_tilde(const ceammc::PdArgs& args)
        : FaustExternal(args)
    {
    }
};

#endif
