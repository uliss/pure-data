declare name "flt.resonbp";

import("stdfaust.lib");

freq = vslider("freq [unit:Hz]", 1000, 20, 20000, 0.1) : si.smoo;
Q = vslider("q", 80, 0.1, 300, 0.1) : si.smoo;

process = fi.resonbp(freq, Q, 1);
