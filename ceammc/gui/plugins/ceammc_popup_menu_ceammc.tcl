{ceammc
    {array {
        array.bpm array.copy array.do array.each array.fill array.minmax
        array.set array.stretch array.vplay
    }}
    {base {
        function function.call gain~ matrix~ metro.pattern metro.seq mix~
        radio window xfade2~ xfade~
    }}
    {conv {
        array.p2s array.s2p conv.amp2dbfs conv.bpm2hz conv.bpm2ms conv.bpm2sec
        conv.cc2amp conv.dbfs2amp conv.lin2curve conv.lin2exp conv.lin2lin
        conv.midi2freq conv.pitch2midi conv.samp2sec conv.sec2samp
        conv.sec2str conv.str2sec
    }}
    {data {
        data.dict data.fifo data.float data.int data.list data.mlist data.set
        data.set2list dict.contains dict.get dict.keys dict.size dict.values
        mlist.flatten set.contains set.diff set.equal set.intersect set.size
        set.symdiff set.union
    }}
    {dyn {
        dyn.comp2~ dyn.comp~ dyn.gate2~ dyn.gate~ dyn.limit2~ dyn.limit~
        dyn.softclip~
    }}
    {env {
        env.adsr~ env.ar~ env.asr~ env.concat env.follow~ env.mix env.smooth~
        env.tscale env.tshift env.vscale env2array env2vline envelope
        vline2env
    }}
    {flow {
        expand_env flow.append flow.change flow.count flow.demultiplex
        flow.demultiplex2~ flow.demultiplex~ flow.gate flow.group
        flow.interval flow.less flow.less_eq flow.multiplex flow.multiplex2~
        flow.multiplex~ flow.once flow.pass flow.pass_if flow.reject
        flow.reject_if flow.route flow.speedlim flow.split flow.sync flow.tee~
        replace
    }}
    {flt {
        flt.biquad~ flt.bpf12~ flt.bpf24~ flt.c_bpf~ flt.c_highshelf~
        flt.c_hpf~ flt.c_lowshelf~ flt.c_lpf~ flt.c_notch~ flt.c_peak~
        flt.dcblock2~ flt.dcblock~ flt.eq_peak_cq~ flt.eq_peak~ flt.highshelf~
        flt.hpf12~ flt.hpf24~ flt.lowshelf~ flt.lpf12~ flt.lpf24~
        flt.moog_vcf~ flt.notch~ flt.resonbp~
    }}
    {fx {
        fx.distortion~ fx.drone_box~ fx.echo~ fx.flanger~ fx.freeverb2~
        fx.freeverb~ fx.freqshift~ fx.greyhole~ fx.looper~ fx.pitchshift~
        fx.sdelay~ fx.wahwah~ fx.zita_rev1~
    }}
    {global {
        global.dict global.float global.int global.list global.mlist
        global.set
    }}
    {hw {
        hw.arduino
    }}
    {lfo {
        lfo.impulse~ lfo.pulse~ lfo.square~ lfo.tri~
    }}
    {list {
        list.^at list.^contains list.^search list.all_of list.any_of
        list.append list.apply_to list.at list.choice list.contains list.count
        list.count_if list.delta list.distribution list.do list.each
        list.enumerate list.equal list.first list.gen list.histogram
        list.insert list.integrator list.last list.length list.max list.mean
        list.min list.none_of list.normalize list.pass_if list.prepend
        list.product list.range list.reduce list.remove list.remove_if
        list.repack list.repeat list.resize list.reverse list.rldecode
        list.rlencode list.rotate list.route list.search list.separate
        list.seq list.set list.shift list.shuffle list.slice list.sort
        list.sort_with list.split list.stretch list.sum list.unique
        list.unpack list.unzip list.walk list.zip
    }}
    {live {
        live.capture~
    }}
    {local {
        local.dict local.float local.int local.list local.mlist local.set
    }}
    {math {
        math.abs math.acos math.acosh math.and math.approx math.asin
        math.asinh math.atan math.atanh math.cbrt math.ceil math.cos math.cosh
        math.div math.e math.exp math.exp2 math.expr math.floor math.gcd
        math.inf math.lcm math.log math.log10 math.log2 math.mul math.nan
        math.neg math.or math.pi math.polyeval math.reciprocal math.round
        math.round~ math.sign math.sin math.sinh math.sqrt math.squared
        math.tan math.tanh math.trunc
    }}
    {midi {
        midi.ctl2str midi.event2ctl midi.event2note midi.event2prg midi.file
        midi.key2str midi.prg2str midi.track
    }}
    {misc {
        click~ fluid~ modplug~ speech.flite
    }}
    {msg {
        msg
    }}
    {noise {
        noise.crackle~ noise.lfreq0~ noise.lfreq~ noise.pink~ noise.white~
    }}
    {osc {
        osc.blit~ osc.impulse~ osc.pulse~ osc.saw~ osc.sinfb~ osc.square~
        osc.tri~
    }}
    {patch {
        canvas.current canvas.top patch.args
    }}
    {path {
        path.basename path.dirname path.exists path.lsdir
    }}
    {predicates {
        is_any is_bang is_data is_even is_file is_float is_list is_odd
        is_pointer is_symbol
    }}
    {preset {
        preset.float preset.list preset.storage preset.symbol
    }}
    {property {
        prop.get prop.get~ prop.set
    }}
    {proto {
        proto.firmata
    }}
    {random {
        random.discrete random.float random.gauss random.int random.linear
        random.pw_const random.pw_lin
    }}
    {snd {
        snd.file
    }}
    {spat {
        pan.cos~ pan.lin~ pan.spread~ pan.sqrt~ spat.pan4~ spat.pan8~
    }}
    {string {
        string string.contains string.ends_with string.equal string.format
        string.join string.length string.remove string.replace string.split
        string.starts_with string.substr string2symbol
    }}
    {symbol {
        symbol.equal symbol.length symbol.num_compare
    }}
    {synth {
        synth.bee3~ synth.birds~ synth.church_bell~ synth.dubdub~
        synth.eguitar~ synth.fgrain~ synth.ks~ synth.marimba~ synth.rhodey~
        synth.risset_arp~ synth.risset_tone~ synth.shakers~ synth.wurley~
    }}
    {system {
        system.cursor system.getenv system.hostname system.memsize
        system.memused system.screen_size
    }}
    {ui {
        tl.bang tl.cue tl.transport ui.aview ui.bang ui.colorpanel ui.display
        ui.dsp~ ui.env ui.gain~ ui.icon ui.incdec ui.keyboard ui.knob ui.label
        ui.link ui.matrix ui.menu ui.meter~ ui.number ui.number~ ui.preset
        ui.radio ui.rslider ui.scope~ ui.slider ui.slider2d ui.sliders
        ui.spectroscope~ ui.tab ui.toggle
    }}
    {vector {
        vector.distance vector.dot vector.length vector.normalize
    }}
}