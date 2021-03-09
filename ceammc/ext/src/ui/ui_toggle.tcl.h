// this is autogenerated file: do not edit
// clang-format off
#ifndef ui_toggle_tcl_h_
#define ui_toggle_tcl_h_
const char* ui_toggle_tcl = 
"namespace eval ::ui {\n"
"proc toggle_update {cnv id w h zoom color state} {\n"
"    set c [::ceammc::ui::widget_canvas $cnv $id]\n"
"    set t [::ceammc::ui::widget_tag $id]\n"
"    $c delete $t\n"
"    if { $state == 0 } { return }\n"
"    set xpad [expr floor($w * 0.1)]\n"
"    set ypad [expr floor($h * 0.1)]\n"
"    if {$xpad > 16} { set xpad 16 }\n"
"    if {$ypad > 16} { set ypad 16 }\n"
"    if {$zoom == 1} {set corr 1} {set corr 0}\n"
"    set x0 [expr $xpad + $corr]\n"
"    set y0 [expr $ypad + $corr]\n"
"    set x1 [expr $w - $xpad]\n"
"    set y1 [expr $h - $ypad]\n"
"    set wd [expr 1 + $zoom]\n"
"    if {$w>30} {set wd [expr $wd + $xpad*0.5]}\n"
"    $c create line $x0 $y0 $x1 $y1 -fill $color -width $wd -capstyle butt -tags $t\n"
"    $c create line $x0 $y1 $x1 $y0 -fill $color -width $wd -capstyle butt -tags $t\n"
"}\n"
"}\n"
;
#endif
// clang-format on
