set(DOC_FILES
    an.onset
    an.onset~
    an.pitchtrack~
    an.rms~
    array.bpm
    array.copy
    array.do
    array.each
    array.fill
    array.hist
    array.mean
    array.minmax
    array.p2s
    array.play~
    array.plot
    array.plot~
    array.resample
    array.rms
    array.s2p
    array.set
    array.stddev
    array.stretch
    array.sum
    array.sum2
    array.variance
    array.vplay
    array.window
    canvas.current
    canvas.dir
    canvas.name
    canvas.path
    canvas.top
    ceammc.search
    chaos.gbman0
    chaos.gbman0~
    chaos.jong
    chaos.logistic
    chaos.std0
    chaos.std0~
    click~
    conv.amp2dbfs
    conv.amp2dbfs~
    conv.bits2bang
    conv.bits2int
    conv.bits2note
    conv.bits2pos
    conv.bpm2hz
    conv.bpm2ms
    conv.bpm2sec
    conv.car2pol
    conv.cc2amp
    conv.dbfs2amp
    conv.dbfs2amp~
    conv.degree2key
    conv.int2bits
    conv.hex2int
    conv.lin2curve
    conv.lin2exp
    conv.lin2lin
    conv.lin2lin~
    conv.list2props
    conv.midi2freq
    conv.ms2bpm
    conv.ms2samp
    conv.ms2samp~
    conv.phase2rad
    conv.phase2rad~
    conv.pitch2midi
    conv.pol2car
    conv.rad2phase
    conv.rad2phase~
    conv.samp2ms
    conv.samp2ms~
    conv.samp2sec
    conv.sec2bpm
    conv.sec2samp
    conv.sec2str
    conv.sig2float~
    conv.str2sec
    data.copy
    data.fifo
    data.float
    data.dict
    data.int
    data.list
    data.mlist
    data.set
    data.set2list
    dict.contains
    dict.each
    dict.from_list
    dict.get
    dict.keys
    dict.pass
    dict.reject
    dict.size
    dict.to_list
    dict.values
    dyn.comp2~
    dyn.comp~
    dyn.gate2~
    dyn.gate~
    dyn.limit2~
    dyn.limit~
    dyn.softclip~
    envelope
    env.mix
    env.tshift
    env.tscale
    env.vscale
    env.concat
    env.adsr~
    env.asr~
    env.ar~
    env.follow~
    env.smooth~
    env2array
    env2vline
    vline2env
    expand_env
    flow.append
    flow.change
    flow.count
    flow.delay
    flow.demultiplex
    flow.demultiplex2~
    flow.demultiplex~
    flow.dup
    flow.gate
    flow.greater
    flow.greater_eq
    flow.group
    flow.interval
    flow.less
    flow.less_eq
    flow.list2many
    flow.match
    flow.mem
    flow.multiplex
    flow.multiplex2~
    flow.multiplex~
    flow.once
    flow.pack
    flow.pass
    flow.pass_if
    flow.pipe
    flow.reject
    flow.reject_if
    flow.ring
    flow.route
    flow.queue
    flow.select
    flow.space
    flow.speedlim
    flow.split
    flow.stack
    flow.sync
    flow.sync_pack
    flow.tee~
    flt.biquad~
    flt.bpf12~
    flt.bpf24~
    flt.c_apf
    flt.c_bpf~
    flt.c_highshelf~
    flt.c_hpf
    flt.c_hpf~
    flt.c_lowshelf~
    flt.c_lpf
    flt.c_lpf~
    flt.c_notch
    flt.c_notch~
    flt.c_pole
    flt.c_peak~
    flt.dcblock2~
    flt.dcblock~
    flt.eq10~
    flt.eq_peak_cq~
    flt.eq_peak~
    flt.fb_comb~
    flt.fbank5x1~
    flt.ff_comb~
    flt.freqz
    flt.freqz~
    flt.highshelf~
    flt.hpf12~
    flt.hpf24~
    flt.lowshelf~
    flt.lpf12~
    flt.lpf24~
    flt.median
    flt.moog_vcf~
    flt.notch~
    flt.resonbp~
    fluid~
    function
    function.call
    fx.bitdown~
    fx.chorus~
    fx.distortion~
    fx.distortion1~
    fx.distortion2~
    fx.distortion3~
    fx.drive~
    fx.drone_box~
    fx.echo~
    fx.flanger~
    fx.freeverb2~
    fx.freeverb~
    fx.freqshift~
    fx.granulator~
    fx.greyhole~
    fx.infrev~
    fx.looper~
    fx.pitchshift~
    fx.pitchshift_s~
    fx.sdelay~
    fx.vocoder~
    fx.wahwah~
    fx.zita_rev1~
    gain~
    global.float
    global.dict
    global.int
    global.list
    global.mlist
    global.set
    hoa.2d.decoder~
    hoa.2d.encoder~
    hoa.2d.map~
    hoa.2d.optim~
    hoa.2d.projector~
    hoa.2d.recomposer~
    hoa.2d.rotate~
    hoa.2d.wider~
    hoa.in
    hoa.in~
    hoa.out
    hoa.out~
    hoa.process~
    hoa.scope~
    hoa.@process
    hw.apple_smc
    hw.apple_sms
    hw.arduino
    hw.cpu_temp
    hw.display
    hw.kbd_light
    hw.serial
    is_any
    is_bang
    is_data
    is_dict
    is_even
    is_file
    is_float
    is_list
    is_odd
    is_pointer
    is_symbol
    lang.faust~
    lfo.+pulse~
    lfo.+saw~
    lfo.+square~
    lfo.+tri~
    lfo.impulse~
    lfo.saw~
    lfo.square~
    lfo.tri~
    lfo.pulse~
    list.^at
    list.^contains
    list.^search
    list.all_of
    list.any_of
    list.append
    list.apply_to
    list.at
    list.choice
    list.contains
    list.count
    list.count_if
    list.delta
    list.distribution
    list.do
    list.each
    list.enumerate
    list.equal
    list.first
    list.gen
    list.histogram
    list.insert
    list.integrator
    list.last
    list.length
    list.max
    list.mean
    list.min
    list.none_of
    list.normalize
    list.pass_if
    list.prepend
    list.product
    list.range
    list.reduce
    list.remove
    list.remove_if
    list.repack
    list.repeat
    list.resample
    list.resize
    list.reverse
    list.rldecode
    list.rlencode
    list.rotate
    list.route
    list.search
    list.separate
    list.set
    list.seq
    list.shift
    list.shuffle
    list.slice
    list.sort
    list.sort_with
    list.split
    list.stretch
    list.sum
    list.unique
    list.unpack
    list.unzip
    list.walk
    list.zip
    live.capture~
    loadexpr
    local.float
    local.dict
    local.int
    local.list
    local.mlist
    local.set
    logger
    math.abs
    math.abs~
    math.acos
    math.acos~
    math.acosh
    math.acosh~
    math.and
    math.approx
    math.asin
    math.asin~
    math.asinh
    math.asinh~
    math.atan
    math.atan~
    math.atanh
    math.atanh~
    math.cabs~
    math.carg~
    math.cbrt
    math.cbrt~
    math.cdiv~
    math.ceil
    math.ceil~
    math.cexp~
    math.cmul~
    math.cos
    math.cos~
    math.cosh
    math.cosh~
    math.div
    math.e
    math.erf
    math.erf~
    math.exp
    math.exp~
    math.exp2
    math.exp2~
    math.expr
    math.floor
    math.floor~
    math.gamma
    math.gamma~
    math.gcd
    math.inf
    math.inf~
    math.lcm
    math.lgamma
    math.lgamma~
    math.log
    math.log~
    math.log10
    math.log10~
    math.log2
    math.log2~
    math.mul
    math.nan
    math.nan~
    math.neg
    math.or
    math.pi
    math.pi~
    math.polyeval
    math.reciprocal
    math.reciprocal~
    math.round
    math.round~
    math.sign
    math.sin
    math.sin~
    math.sinh
    math.sinh~
    math.sqrt
    math.sqrt~
    math.squared
    math.squared~
    math.sync_add
    math.sync_and
    math.sync_div
    math.sync_eq
    math.sync_ge
    math.sync_gt
    math.sync_le
    math.sync_lt
    math.sync_mod
    math.sync_mul
    math.sync_ne
    math.sync_or
    math.sync_sub
    math.sync_xor
    math.sync_lshift
    math.sync_rshift
    math.tan
    math.tan~
    math.tanh
    math.tanh~
    math.trunc
    math.trunc~
    matrix~
    metro.pattern
    metro.random
    metro.seq
    midi.cc
    midi.clock
    midi.ctl2str
    midi.event2ctl
    midi.event2note
    midi.event2prg
    midi.file
    midi.kbd
    midi.key2str
    midi.oct
    midi.prg2str
    midi.sustain
    midi.sysex
    midi.track
    midi.tuning
    midi.vramp
    midi.vrand
    mix~
    mlist.flatten
    modplug~
    msg
    msg.after
    msg.onload
    net.host2ip
    noise.baker
    noise.clifford
    noise.collatz
    noise.crackle~
    noise.duffing
    noise.ginger
    noise.henon
    noise.henon_heilles
    noise.henon_phase
    noise.henonf
    noise.ikeda
    noise.lfreq0~
    noise.lfreq~
    noise.lorenz
    noise.lyapunov
    noise.navier_stokes
    noise.pink~
    noise.rossler
    noise.stein
    noise.torus
    noise.verhulst
    noise.white~
    nsig~
    obj.props
    osc.blit~
    osc.impulse~
    osc.pulse~
    osc.saw~
    osc.saw4~
    osc.sin~
    osc.sinfb~
    osc.square~
    osc.tri~
    pan.cos~
    pan.lin~
    pan.linsig~
    pan.spread~
    pan.sqrt~
    patch.args
    patch.deps
    patch.props
    patch.tree
    path.basename
    path.dirname
    path.exists
    path.is_dir
    path.lsdir
    plot.hist~
    plot.geomspace~
    plot.linspace~
    plot.logspace~
    plot.response~
    preset.float
    preset.list
    preset.storage
    preset.symbol
    prop
    prop.declare
    prop.get
    prop.get~
    prop.join
    prop.set
    prop.split
    proto.firmata
    proto.midi
    proto.xtouch_ext
    proto.sp.alpaca
    radio
    random.atom
    random.float
    random.gauss
    random.int
    random.linear
    random.pw_lin
    random.pw_const
    random.discrete
    replace
    route.float
    rtree.to_list
    set.contains
    set.diff
    set.equal
    set.intersect
    set.size
    set.symdiff
    set.union
    sequencer
    seq.arp
    seq.bangs
    seq.counter
    seq.life
    seq.matrix
    seq.nbangs
    seq.phasor
    seq.toggles
    snd.file
    spat.pan4~
    spat.pan8~
    spat.zita6x8~
    speech.flite
    speech.flite~
    string
    string.contains
    string.ends_with
    string.equal
    string.format
    string.join
    string.length
    string.match
    string.remove
    string.replace
    string.split
    string.starts_with
    string.substr
    string2symbol
    symbol.equal
    symbol.length
    symbol.num_compare
    symbol2intlist
    symbol2any
    sync
    synth.bee3~
    synth.birds~
    synth.church_bell~
    synth.dubdub~
    synth.dx7~
    synth.eguitar~
    synth.fgrain~
    synth.harpsichord~
    synth.glass_harm~
    synth.glitch~
    synth.ks~
    synth.marimba~
    synth.piano~
    synth.rhodey~
    synth.risset_arp~
    synth.risset_tone~
    synth.russian_bell~
    synth.shakers~
    synth.sitar~
    synth.wurley~
    system.colorpanel
    system.cursor
    system.exit
    system.getenv
    system.hostname
    system.memsize
    system.memused
    system.exec
    system.exit
    system.screen_size
    tl.bang
    tl.cue
    tl.timeline
    tl.toggle
    tl.transport
    ui.aview
    ui.bang
    ui.button
    ui.colorpanel
    ui.display
    ui.dsp~
    ui.env
    ui.faust~
    ui.filter
    ui.filter~
    ui.gain~
    ui.gain2~
    ui.icon
    ui.incdec
    ui.keyboard
    ui.knob
    ui.matrix
    ui.menu
    ui.midi
    ui.mouse_filter
    ui.mouse_route
    ui.number
    ui.label
    ui.link
    ui.number~
    ui.plot~
    ui.polar
    ui.preset
    ui.scope~
    ui.slider
    ui.slider2d
    ui.sliders
    ui.radio
    ui.rslider
    ui.tab
    ui.spectroscope~
    ui.toggle
    ui.meter~
    window
    xfade~
    xfade2~
    xdac~
)
