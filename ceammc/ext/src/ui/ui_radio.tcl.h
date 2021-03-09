// this is autogenerated file: do not edit
// clang-format off
#ifndef ui_radio_tcl_h_
#define ui_radio_tcl_h_
const char* ui_radio_tcl = 
"namespace eval ::ui {\n"
"proc radio_draw_single {c t w h zoom orient states color} {\n"
"    set min_size [expr 2 * $zoom]\n"
"    if { $orient == \"v\" } {\n"
"        set cell_size $w\n"
"        set pad [expr round($cell_size/5.0)]\n"
"        if { $pad < $min_size } { set pad $min_size }\n"
"        set i 0\n"
"        foreach x [split $states {}] {\n"
"            if { $x == \"1\" } {\n"
"                set y0 [expr $i*$cell_size + $pad]\n"
"                set y1 [expr ($i+1)*$cell_size - $pad]\n"
"                set x0 $pad\n"
"                set x1 [expr $w - $pad]\n"
"                $c create rectangle $x0 $y0 $x1 $y1 -fill $color -outline $color -width $zoom -tags $t\n"
"                break\n"
"            }\n"
"            incr i\n"
"        }\n"
"    } else {\n"
"        set cell_size $h\n"
"        set pad [expr round($cell_size/5.0)]\n"
"        if { $pad < $min_size } { set pad $min_size }\n"
"        set i 0\n"
"        foreach x [split $states {}] {\n"
"            if { $x == \"1\" } {\n"
"                set x0 [expr $i*$cell_size + $pad]\n"
"                set x1 [expr ($i+1)*$cell_size - $pad]\n"
"                set y0 $pad\n"
"                set y1 [expr $h - $pad]\n"
"                $c create rectangle $x0 $y0 $x1 $y1 -fill $color -outline $color -width $zoom -tags $t\n"
"                break\n"
"            }\n"
"            incr i\n"
"        }\n"
"    }\n"
"}\n"
"proc radio_draw_cross {c t x y w h zoom color} {\n"
"    set xpad [expr floor($w * 0.1)]\n"
"    set ypad [expr floor($h * 0.1)]\n"
"    if {$xpad > 16} { set xpad 16 }\n"
"    if {$ypad > 16} { set ypad 16 }\n"
"    if {$zoom == 1} {set corr 1} {set corr 0}\n"
"    set x0 [expr $x + $xpad + $corr]\n"
"    set y0 [expr $y + $ypad + $corr]\n"
"    set x1 [expr $x + $w - $xpad]\n"
"    set y1 [expr $y + $h - $ypad]\n"
"    set wd [expr 1 + $zoom]\n"
"    if {$w>30} {set wd [expr $wd + $xpad*0.5]}\n"
"    $c create line $x0 $y0 $x1 $y1 -fill $color -width $wd -capstyle butt -tags $t\n"
"    $c create line $x0 $y1 $x1 $y0 -fill $color -width $wd -capstyle butt -tags $t\n"
"}\n"
"proc radio_draw_multi {c t w h zoom orient states color} {\n"
"    if { $orient == \"v\" } {\n"
"        set cell_size $w\n"
"        set i 0\n"
"        foreach x [split $states {}] {\n"
"            if { $x == \"1\" } {\n"
"                set y0 [expr $i*$cell_size]\n"
"                radio_draw_cross $c $t 0 $y0 $cell_size $cell_size $zoom $color\n"
"            }\n"
"            incr i\n"
"        }\n"
"    } else {\n"
"        set cell_size $h\n"
"        set i 0\n"
"        foreach x [split $states {}] {\n"
"            if { $x == \"1\" } {\n"
"                set x0 [expr $i*$cell_size]\n"
"                radio_draw_cross $c $t $x0 0 $cell_size $cell_size $zoom $color\n"
"            }\n"
"            incr i\n"
"        }\n"
"    }\n"
"}\n"
"proc radio_update {cnv id w h zoom orient mode states act_color out_color} {\n"
"    set c [::ceammc::ui::widget_canvas $cnv $id]\n"
"    set t [::ceammc::ui::widget_tag $id]\n"
"    $c delete $t\n"
"    set num_cells [string length $states]\n"
"    if { $orient == \"v\" } {\n"
"        set cell_size $w\n"
"        for { set i 1 } { $i < $num_cells } { incr i } {\n"
"            set y [expr $cell_size * $i]\n"
"            $c create line 0 $y $w $y -fill $out_color -width $zoom -capstyle butt -tags $t\n"
"        }\n"
"    } else {\n"
"        set cell_size $h\n"
"        for { set i 1 } { $i < $num_cells } { incr i } {\n"
"            set x [expr $cell_size * $i]\n"
"            $c create line $x 0 $x $h -fill $out_color -width $zoom -capstyle butt -tags $t\n"
"        }\n"
"    }\n"
"    if { $mode == \".\" } {\n"
"        radio_draw_single $c $t $w $h $zoom $orient $states $act_color\n"
"    } else {\n"
"        radio_draw_multi  $c $t $w $h $zoom $orient $states $act_color\n"
"    }\n"
"}\n"
"}\n"
;
#endif
// clang-format on
