declare name 		"capture";
declare version 	"1.0";
declare author 		"Grame";
declare license 	"BSD";
declare copyright 	"(c)GRAME 2006";

//-------------------------------------------------
// Capture : record up to 8s of sound and
// playback the recorded sound in loop
//-------------------------------------------------

import("stdfaust.lib");

TOTAL = 32;
B = checkbox("gate"); // Capture sound while pressed
I = int(B);             // convert button signal from float to integer
R = (I-I') <= 0;        // Reset capture when button is pressed
D = (+(I):*(R))~_;      // Compute capture duration while button is pressed: 0..NNNN0..MMM

capture = *(B) : (+ : de.delay(TOTAL * ma.SR, D-1)) ~ *(1.0-B);

process	= capture;
