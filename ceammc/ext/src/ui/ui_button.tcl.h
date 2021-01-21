// this is autogenerated file: do not edit
// clang-format off
#ifndef ui_button_tcl_h_
#define ui_button_tcl_h_
const char* ui_button_tcl = 
"namespace eval ::ui {\n"
"proc button_delete {id cnv} {\n"
"    $cnv delete ${id}_#all\n"
"}\n"
"proc button_create {id cnv w h c0 c1 state} {\n"
"    if { $state == 1 } { set c $c1 } { set c $c0 }\n"
"    set xpad [expr {round($w/10)} + 1]\n"
"    set ypad [expr {round($h/10)} + 1]\n"
"    set x0 [expr $xpad + 1]\n"
"    set x1 [expr ($w - $xpad) + 1]\n"
"    set y0 [expr $ypad + 1]\n"
"    set y1 [expr ($h - $ypad) + 1]\n"
"    $cnv create rectangle $x0 $y0 $x1 $y1 -fill $c -width 0 -tags ${id}_#all\n"
"}\n"
"}\n"
;
#endif
// clang-format on
