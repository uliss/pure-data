declare name "synth.harpsichord";
declare description "Nonlinear WaveGuide Commuted Harpsichord";
declare author "Romain Michon (rmichon@ccrma.stanford.edu)";
declare copyright "Romain Michon";
declare version "1.0";
declare licence "STK-4.3"; // Synthesis Tool Kit 4.3 (MIT style license);
declare description "A commuted WaveGuide Harpsichord."; 

import("instruments.lib");
spn = library("spn.lib");
inst = library("ceammc_instruments.lib");
ui = library("ceammc_ui.lib");
ci = library("ceammc.lib");
co = library("compressors.lib");

//==================== GUI SPECIFICATION ================

//freq = nentry("freq [1][unit:Hz] [tooltip:Tone frequency]",440,20,20000,1);
freq = hslider("pitch", spn.C3, spn.C1, spn.C7, 0.001) : ba.midikey2hz;
btn = ui.fgate;
gain = btn : ci.clip(0, 1) : si.smoo;
gate = btn > 0;

typeModulation = nentry("modtype
[tooltip: 0=theta is modulated by the incoming signal; 1=theta is modulated by the averaged incoming signal;
2=theta is modulated by the squared incoming signal; 3=theta is modulated by a sine wave of frequency freqMod;
4=theta is modulated by a sine wave of frequency freq;]",0,0,4,1) : int;

nonLinearity = hslider("nonlin
[tooltip:Nonlinearity factor (value between 0 and 1)]",0,0,1,0.01);

frequencyMod = hslider("modfreq
[unit:Hz][tooltip:Frequency of the sine wave for the modulation of theta (works if Modulation Type=3)]",220,20,1000,0.1);

//==================== PROCESSING ================

//----------------------- Nonlinear filter ----------------------------
//nonlinearities are created by the nonlinear passive allpass ladder filter declared in miscfilter.lib

//nonlinear filter order
nlfOrder = 6; 

//nonLinearModultor is declared in instruments.lib, it adapts allpassnn from miscfilter.lib 
//for using it with waveguide instruments
NLFM =  nonLinearModulator((nonLinearity : si.smoo),1,freq,
     typeModulation,(frequencyMod : si.smoo),nlfOrder);

//----------------------- Synthesis parameters computing and functions declaration ----------------------------

//string excitation
soundBoard = dryTapAmp*no.noise
	with{
                dryTapAmpT60 = ffunction(float getValueDryTapAmpT60(float), "harpsichord.h","");
                noteCutOffTime = freq : dryTapAmpT60*gain;
		dryTapAmp = asympT60(0.15,0,noteCutOffTime,gate);
	};	

//loopfilter is a biquad filter whose coefficients are extracted from a C++ file using the foreign function mechanism
loopFilter = fi.TF2(b0,b1,b2,a1,a2)
	   with{
		//functions are imported from the C++ file
                loopFilterb0 = ffunction(float getValueLoopFilterb0(float), "harpsichord.h","");
                loopFilterb1 = ffunction(float getValueLoopFilterb1(float), "harpsichord.h","");
                loopFilterb2 = ffunction(float getValueLoopFilterb2(float), "harpsichord.h","");
                loopFiltera1 = ffunction(float getValueLoopFiltera1(float), "harpsichord.h","");
                loopFiltera2 = ffunction(float getValueLoopFiltera2(float), "harpsichord.h","");
		//coefficients are extracted from the functions
                b0 = loopFilterb0(freq);
                b1 = loopFilterb1(freq);
                b2 = loopFilterb2(freq);
                a1 = loopFiltera1(freq);
                a2 = loopFiltera2(freq);
	   };

//----------------------- Algorithm implementation ----------------------------

//envelope for string loop resonance time
stringLoopGainT = gate*0.9996 + (gate<1)*releaseLoopGain(freq)*0.9 : si.smoo
with {
    releaseLoopGain = ffunction(float getValueReleaseLoopGain(float), "harpsichord.h","");
};


process = soundBoard : string : stereo : reverb
with {
    //delay length as a number of samples
    delayLength = ma.SR/freq;

    //one string
    string = (*(stringLoopGainT)+_ : de.delay(4096,delayLength) : loopFilter : comp)~NLFM;

    comp = co.compressor_mono(2, 100, 10, 50);
    stereo = inst.stereoizer(ma.SR/freq);
    reverb = inst.reverb2;
};


