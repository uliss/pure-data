// this is autogenerated file: do not edit
// clang-format off
#ifndef ui_display_tcl_h_
#define ui_display_tcl_h_
const char* ui_display_tcl = 
"namespace eval ::ui {\n"
"namespace eval display {\n"
"    variable font_size 11\n"
"    variable font_family \"Helvetica\"\n"
"}\n"
"switch -- $::windowingsystem {\n"
"    \"aqua\" { }\n"
"    \"x11\"  { }\n"
"    \"win32\" {\n"
"        set display::font_size 7\n"
"    }\n"
"}\n"
"proc display_type_font { zoom } { return \"$display::font_family [expr $zoom * $display::font_size] normal roman\" }\n"
"proc display_single_line { type } {\n"
"    switch $type {\n"
"        bang    { return 1 }\n"
"        float   { return 1 }\n"
"        symbol  { return 1 }\n"
"        default { return 0 }\n"
"    }\n"
"}\n"
"proc display_txt_width { c tag } {\n"
"   lassign [$c bbox $tag] tx0 ty0 tx1 ty1\n"
"   return [expr $tx1 - $tx0]\n"
"}\n"
"proc display_txt_height { c tag } {\n"
"   lassign [$c bbox $tag] tx0 ty0 tx1 ty1\n"
"   return [expr abs($ty1 - $ty0)]\n"
"}\n"
"proc display_update {cnv id rid w h zoom hauto bdcolor bgcolor txtcolor typecolor showtype type txt} {\n"
"    set c [::ceammc::ui::widget_canvas $cnv $id]\n"
"    set t [::ceammc::ui::widget_tag $id]\n"
"    $c delete $t\n"
"    # set bg\n"
"    ::ceammc::ui::widget_bg $cnv $id $bgcolor\n"
"    set txpad [expr $zoom*2+1]\n"
"    set typad [expr $zoom*2+1]\n"
"    set tx $txpad\n"
"    set ty $typad\n"
"    set ft [display_type_font $zoom]\n"
"    set x 0\n"
"    set typeh 0\n"
"    if { $showtype == 1 } {\n"
"        set ttag \"${t}_t\"\n"
"        # draw type text\n"
"        $c create text $tx $ty -text $type -anchor nw -justify left \\\n"
"            -font $ft -fill $txtcolor -width 0 -tags [list $t $ttag]\n"
"        set typew [display_txt_width $c $ttag]\n"
"        set typeh [display_txt_height $c $ttag]\n"
"        set x [expr (2*$txpad) + $typew]\n"
"        # draw type filled rectangle\n"
"        set ttagr \"${t}_tr\"\n"
"        $c create rectangle 0 0 $x $h -fill $typecolor -outline $typecolor -width $zoom -tags [list $t $ttagr]\n"
"        $c raise $ttag $ttagr\n"
"        # draw type text separator line\n"
"        $c create line $x 0 $x $h -fill $bdcolor -width $zoom -tag $t\n"
"    }\n"
"    # draw main text\n"
"    set tx [expr $x + $txpad]\n"
"    set ty $typad\n"
"    if {$hauto == 1} {\n"
"        set tw 0\n"
"        if { ![display_single_line $type] } {\n"
"            set minw [expr 150*$zoom]\n"
"            set tw $minw\n"
"        }\n"
"    } {\n"
"        set tw [expr $w - ($tx + $txpad)]\n"
"    }\n"
"    set tt \"${t}_m\"\n"
"    $c create text $tx $ty -text $txt -anchor nw -justify left \\\n"
"        -font $ft -fill $txtcolor -width $tw -tags [list $t $tt]\n"
"    if {$hauto == 1} {\n"
"        switch $type {\n"
"            bang {\n"
"                # resize to min size\n"
"                pdsend \"$rid .resize [expr $tx+15] 10\"\n"
"            }\n"
"            float {\n"
"                set tw [display_txt_width $c $tt]\n"
"                set dispw [expr $tx + $tw + (2*$txpad)]\n"
"                if { $dispw != $w } {\n"
"                    # resize to min height\n"
"                    pdsend \"$rid .resize $dispw 10\"\n"
"                }\n"
"            }\n"
"            symbol {\n"
"                set tw [display_txt_width $c $tt]\n"
"                set dispw [expr $tx + $tw + (2*$txpad)]\n"
"                if { $dispw != $w } {\n"
"                    # resize to min height\n"
"                    pdsend \"$rid .resize $dispw 10\"\n"
"                }\n"
"            }\n"
"            default {\n"
"                set nw $w\n"
"                set tw [display_txt_width $c $tt]\n"
"                set dispw [expr $tx + $tw + (2*$txpad)]\n"
"                if { $dispw != $w } { set nw $dispw }\n"
"                set nh 5\n"
"                set th [display_txt_height $c $tt]\n"
"                set disph [expr $th + $typad]\n"
"                if { $typeh > $nh } { set nh $typeh }\n"
"                if { $disph > $nh } { set nh $disph }\n"
"                if { $nh != $h || $nw != $w } {\n"
"                    pdsend \"$rid .resize $nw $nh\"\n"
"                }\n"
"            }\n"
"        }\n"
"    }\n"
"}\n"
"}\n"
;
#endif
// clang-format on
