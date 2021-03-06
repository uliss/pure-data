// this is autogenerated file: do not edit
// clang-format off
#ifndef tcl_nui_tcl_h_
#define tcl_nui_tcl_h_
const char* tcl_nui_tcl = 
"namespace eval ::nui {\n"
"proc pd_canvas { cnv } { return \".x${cnv}.c\" }\n"
"namespace eval utils {\n"
"    proc fix_mac_state {n} { if { $n > 256 } { return [expr $n & 0xFF ] } { return $n } }\n"
"    proc fix_win32_alt {n} {\n"
"        if { $n & 131072 } {\n"
"            incr n -131072\n"
"            set n [expr $n | 16]\n"
"        }\n"
"        return $n\n"
"    }\n"
"    proc fix_win32_state {n} {\n"
"        if { $n & 32 } { incr n -32 }\n"
"        return [expr 0xFF & [fix_win32_alt $n]]\n"
"    }\n"
"    proc send_mouse_move {obj x y mod} {\n"
"        switch -- $::windowingsystem {\n"
"            \"aqua\" {\n"
"                # disable mouse dragging for buttons other then first\n"
"                if { $mod < 512 } { pdsend \"$obj mousemove $x $y [fix_mac_state $mod]\" }\n"
"            } \"win32\" {\n"
"                set mod [fix_win32_alt $mod]\n"
"                if { $mod < 512 } { pdsend \"$obj mousemove $x $y [fix_win32_state $mod]\" }\n"
"            } \"default\" {\n"
"                pdsend \"$obj mousemove $x $y $mod\"\n"
"            }\n"
"        }\n"
"    }\n"
"}\n"
"proc widget_canvas { cnv id } { return \".x${cnv}.c.cnv${id}\" }\n"
"proc widget_window { cnv id } { return \".x${cnv}.c.win${id}\" }\n"
"proc widget_w   { w zoom } { expr $w * $zoom + 1 }\n"
"proc widget_h   { h zoom } { expr $h * $zoom + 1 }\n"
"proc widget_tag { id } { return \"#${id}\" }\n"
"proc canvas_motion {cnv id val} {\n"
"    set c  [pd_canvas $cnv]\n"
"    set rx [winfo rootx $c]\n"
"    set ry [winfo rooty $c]\n"
"    set x  [winfo pointerx .]\n"
"    set y  [winfo pointery .]\n"
"    pdtk_canvas_motion $c [expr $x - $rx] [expr $y - $ry] $val\n"
"}\n"
"proc canvas_down {cnv id val} {\n"
"    set c  [pd_canvas $cnv]\n"
"    set rx [winfo rootx $c]\n"
"    set ry [winfo rooty $c]\n"
"    set x  [winfo pointerx .]\n"
"    set y  [winfo pointery .]\n"
"    pdtk_canvas_mouse $c [expr $x - $rx] [expr $y - $ry] 0 $val\n"
"}\n"
"proc canvas_up {cnv id} {\n"
"    set c  [pd_canvas $cnv]\n"
"    set rx [winfo rootx $c]\n"
"    set ry [winfo rooty $c]\n"
"    set x  [winfo pointerx .]\n"
"    set y  [winfo pointery .]\n"
"    pdtk_canvas_mouseup $c [expr $x - $rx] [expr $y - $ry] 0\n"
"}\n"
"proc canvas_right {cnv id} {\n"
"    set c  [pd_canvas $cnv]\n"
"    set rx [winfo rootx $c]\n"
"    set ry [winfo rooty $c]\n"
"    set x  [winfo pointerx .]\n"
"    set y  [winfo pointery .]\n"
"    pdtk_canvas_rightclick $c [expr $x - $rx] [expr $y - $ry] 0\n"
"}\n"
"proc widget_create { cnv id x y w h zoom } {\n"
"    set win [widget_window $cnv $id]\n"
"    set c [widget_canvas $cnv $id]\n"
"    set w [widget_w $w $zoom]\n"
"    set h [widget_h $h $zoom]\n"
"    namespace eval \"nui$id\" {}\n"
"    destroy $c\n"
"    canvas $c -width $w -height $h -bd 0 \\\n"
"        -highlightthickness 0 -insertborderwidth 0 \\\n"
"        -state normal -takefocus 1 -insertwidth 0 -confine 0\n"
"    $c configure -bg #AAAAAA\n"
"    [pd_canvas $cnv] create window $x $y -anchor nw -window $c \\\n"
"        -tags $win -width $w -height $h\n"
"}\n"
"proc widget_bg { cnv id color } {\n"
"    set c [widget_canvas $cnv $id]\n"
"    $c configure -bg $color\n"
"}\n"
"proc widget_erase { cnv id } {\n"
"    set win [widget_window $cnv $id]\n"
"    set c [widget_canvas $cnv $id]\n"
"    [pd_canvas $cnv] delete $win\n"
"    destroy $c\n"
"}\n"
"proc widget_resize { cnv id w h zoom } {\n"
"    set win [widget_window $cnv $id]\n"
"    set c [widget_canvas $cnv $id]\n"
"    set w [widget_w $w $zoom]\n"
"    set h [widget_h $h $zoom]\n"
"    $c configure -width $w -height $h\n"
"    [pd_canvas $cnv] itemconfigure $win -width $w -height $h\n"
"}\n"
"proc widget_move { cnv id x y } {\n"
"    set c [pd_canvas $cnv]\n"
"    set win [widget_window $cnv $id]\n"
"    $c coords $win $x $y\n"
"}\n"
"proc widget_focus { cnv id } {\n"
"    focus [widget_canvas $cnv $id]\n"
"}\n"
"proc widget_mouse_bind { cnv id target args }  {\n"
"    set c [widget_canvas $cnv $id]\n"
"    foreach name $args {\n"
"        set ev \"widget_mouse_${name}_bind\"\n"
"        $ev $c \"#$target\"\n"
"    }\n"
"}\n"
"proc widget_cursor { cnv id name }  {\n"
"    set c [widget_canvas $cnv $id]\n"
"    $c configure -cursor $name\n"
"}\n"
"proc widget_mouse_move_bind  {id obj} { bind $id <Motion> [subst {+::nui::utils::send_mouse_move $obj %x %y %s}] }\n"
"proc widget_mouse_enter_bind {id obj} { bind $id <Enter>  [subst {+pdsend \"$obj mouseenter\"}] }\n"
"proc widget_mouse_leave_bind {id obj} { bind $id <Leave>  [subst {+pdsend \"$obj mouseleave\"}] }\n"
"proc widget_mouse_down_bind {id obj} {\n"
"    switch -- $::windowingsystem {\n"
"        \"win32\" {\n"
"            bind $id <ButtonPress-1> [subst -nocommands {+pdsend \"$obj mousedown %x %y %X %Y [ceammc_fix_win32_state %s]\"}]\n"
"        } \"default\" {\n"
"            bind $id <ButtonPress-1> [subst {+pdsend \"$obj mousedown %x %y %X %Y %s\"}]\n"
"        }\n"
"    }\n"
"}\n"
"proc widget_mouse_up_bind {id obj} {\n"
"    switch -- $::windowingsystem {\n"
"        \"aqua\" {\n"
"            bind $id <ButtonRelease-1> [subst -nocommands {+pdsend \"$obj mouseup %x %y [ceammc_fix_macos_state %s]\"}]\n"
"        } \"win32\" {\n"
"            bind $id <ButtonRelease-1> [subst -nocommands {+pdsend \"$obj mouseup %x %y [ceammc_fix_win32_state %s]\"}]\n"
"        } \"default\" {\n"
"            bind $id <ButtonRelease-1> [subst {+pdsend \"$obj mouseup %x %y %s\"}]\n"
"        }\n"
"    }\n"
"}\n"
"proc widget_mouse_right_bind {id obj} {\n"
"    switch -- $::windowingsystem {\n"
"        \"aqua\" {\n"
"            bind $id <ButtonPress-2> [subst {+pdsend \"$obj rightclick %x %y %X %Y %s\"}]\n"
"            bind $id <Control-ButtonPress-1> [subst {+pdsend \"$obj rightclick %x %y %X %Y %s\"}]\n"
"        } \"win32\" {\n"
"            bind $id <ButtonPress-3> [subst -nocommands {+pdsend \"$obj rightclick %x %y %X %Y [ceammc_fix_win32_state %s]\"}]\n"
"        } \"default\" {\n"
"            bind $id <ButtonPress-3> [subst {+pdsend \"$obj rightclick %x %y %X %Y %s\"}]\n"
"        }\n"
"    }\n"
"}\n"
"if { [catch {package require tooltip} ] } {\n"
"    proc widget_tooltip { cnv model id msg } {}\n"
"} {\n"
"    proc widget_tooltip { cnv model id msg } {\n"
"        set c [widget_canvas $cnv $model]\n"
"        tooltip::tooltip $c -item $id $msg\n"
"    }\n"
"}\n"
"proc item_erase { cnv model tags } {\n"
"    set c [widget_canvas $cnv $model]\n"
"    $c delete $tags\n"
"}\n"
"proc item_move { cnv model tag x y } {\n"
"    set c [widget_canvas $cnv $model]\n"
"    lassign [$c coords $tag] x0 y0 x1 y1\n"
"    set w [expr $x1-$x0]\n"
"    set h [expr $y1-$y0]\n"
"    $c coords $tag $x $y [expr $x+$w] [expr $y+$h]\n"
"}\n"
"namespace eval xlet {\n"
"    proc tag     { id isout }   { if { $isout } { return \"o${id}\" }      { return \"i${id}\" } }\n"
"    proc tag_idx { id n isout } { if { $isout } { return \"o${id}#${n}\" } { return \"i${id}#${n}\" } }\n"
"    proc width  { zoom } { expr 6*$zoom + 1 }\n"
"    proc height { type zoom } { if { $type == \"_\" } { expr $zoom } { expr ($zoom==1) ? 2 : 4 } }\n"
"    proc xpos   { w i n zoom } {\n"
"        set ww [expr $w - [width $zoom]]\n"
"        return [expr round(($ww/($n-1.0)) * $i)]\n"
"    }\n"
"    proc out_ypos { h type zoom } { return [expr $h - [height $type $zoom]] }\n"
"    proc draw_single { cnv id x h zoom type idx ctl_color sig_color isout } {\n"
"        set c [::nui::widget_canvas $cnv $id]\n"
"        if { $isout } { set y [out_ypos $h $type $zoom] } { set y 0 }\n"
"        set x1 [expr $x + [::nui::xlet::width $zoom]]\n"
"        set y1 [expr $y + [::nui::xlet::height $type $zoom]]\n"
"        set t [tag $id $isout]\n"
"        lappend t [tag_idx $id $idx $isout]\n"
"        if {$type == \"_\"} { set color $ctl_color } { set color $sig_color }\n"
"        $c create rectangle $x $y $x1 $y1 -fill $color -outline $color -width 1 -tags $t\n"
"    }\n"
"    proc erase_all { cnv id isout } {\n"
"        set c [::nui::widget_canvas $cnv $id]\n"
"        $c delete [tag $id $isout]\n"
"    }\n"
"    proc draw_multiple { cnv id w h zoom str ctl_color sig_color isout } {\n"
"        set c [::nui::widget_canvas $cnv $id]\n"
"        $c delete [tag $id $isout]\n"
"        set n [string length $str]\n"
"        if { $n == 1 } {\n"
"            draw_single $cnv $id 0 $h $zoom $str 0 $ctl_color $sig_color $isout\n"
"        } elseif { $n > 1 } {\n"
"            set i 0\n"
"            foreach inlet [split $str {}] {\n"
"                set x [::nui::xlet::xpos $w $i $n $zoom]\n"
"                draw_single $cnv $id $x $h $zoom $inlet $i $ctl_color $sig_color $isout\n"
"                incr i\n"
"            }\n"
"        }\n"
"    }\n"
"    proc tooltip { cnv id idx str } {\n"
"        set c [::nui::widget_canvas $cnv $id]\n"
"        set win [::nui::widget_window $cnv $id]\n"
"        set tag [tag_idx $id $idx]\n"
"        xlet_tooltip::create $c $win $cnv $tag 1 $str\n"
"    }\n"
"}\n"
"namespace eval box {\n"
"    proc tag_border { id } { return \"#b${id}\" }\n"
"    proc tag_fill   { id } { return \"#b${id}_bg\" }\n"
"    proc create { cnv model id x y w h zoom border_color fill_color ctl_color sig_color border_width inlets outlets } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set tb [tag_border $id]\n"
"        set tf [tag_fill $id]\n"
"        # zoomed border correction\n"
"        if { $zoom > 1} {\n"
"            set x0 [expr $x+($zoom)/2]\n"
"            set y0 [expr $y+($zoom)/2]\n"
"        } {\n"
"            set x0 $x\n"
"            set y0 $y\n"
"        }\n"
"        set x1 [expr $x+$w]\n"
"        set y1 [expr $y+$h]\n"
"        $c create rectangle $x0 $y0 $x1 $y1 \\\n"
"            -fill {} -outline $border_color -width $border_width -tags $tb\n"
"        $c create rectangle $x0 $y0 $x1 $y1 \\\n"
"            -fill $fill_color -outline {} -width 0 -tags $tf\n"
"        $c lower $tf\n"
"        ::nui::xlet::draw_multiple $cnv $model $w $h $zoom $inlets $ctl_color $sig_color false\n"
"        ::nui::xlet::draw_multiple $cnv $model $w $h $zoom $outlets $ctl_color $sig_color true\n"
"    }\n"
"    proc update { cnv model id w h zoom border_color fill_color ctl_color sig_color border_width inlets outlets } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set tb [tag_border $id]\n"
"        set tf [tag_fill $id]\n"
"        $c itemconfigure $tb -outline $border_color\n"
"        $c itemconfigure $tf -fill $fill_color\n"
"        lassign [$c coords $tb] x0 y0 x1 y1\n"
"        $c coords $tb $x0 $y0 [expr $x0+$w] [expr $y0+$h]\n"
"        $c coords $tf $x0 $y0 [expr $x0+$w] [expr $y0+$h]\n"
"        ::nui::xlet::draw_multiple $cnv $model $w $h $zoom $inlets $ctl_color $sig_color false\n"
"        ::nui::xlet::draw_multiple $cnv $model $w $h $zoom $outlets $ctl_color $sig_color true\n"
"    }\n"
"    proc erase { cnv model id } {\n"
"        ::nui::item_erase $cnv $model [tag $id]\n"
"    }\n"
"    proc move  { cnv model id x y } {\n"
"        ::nui::item_move $cnv $model [tag $id] $x $y\n"
"    }\n"
"}\n"
"namespace eval frame {\n"
"    proc tag { id } { return \"#f${id}\" }\n"
"    proc create { cnv model id x y w h border_color fill_color width } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set t [tag $id]\n"
"        $c create rectangle $x $y [expr $x+$w] [expr $y+$h] \\\n"
"            -fill $fill_color -outline $border_color -width $width -tags $t\n"
"    }\n"
"    proc update { cnv model id w h border_color fill_color } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set t [tag $id]\n"
"        $c itemconfigure $t -outline $border_color -fill $fill_color\n"
"        lassign [$c coords $t] x0 y0 x1 y1\n"
"        $c coords $t $x0 $y0 [expr $x0+$w] [expr $y0+$h]\n"
"    }\n"
"    proc erase { cnv model id } {\n"
"        ::nui::item_erase $cnv $model [tag $id]\n"
"    }\n"
"    proc move  { cnv model id x y } {\n"
"        ::nui::item_move $cnv $model [tag $id] $x $y\n"
"    }\n"
"}\n"
"namespace eval label {\n"
"    proc tag { id } { return \"#l${id}\" }\n"
"    proc create { cnv model id x y width anchor font color txt } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set t [tag $id]\n"
"        $c create text $x $y -fill $color -text $txt -font $font -anchor $anchor -width $width -tags $t\n"
"    }\n"
"    proc update { cnv model id x y width anchor font color txt } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set t [tag $id]\n"
"        $c coords $t $x $y\n"
"        $c itemconfigure $t -fill $color -text $txt -font $font -anchor $anchor -width $width -tags $t\n"
"    }\n"
"    proc erase { cnv model id } {\n"
"        ::nui::item_erase $cnv $model [tag $id]\n"
"    }\n"
"    proc move  { cnv model id x y } {\n"
"        ::nui::item_move $cnv $model [tag $id] $x $y\n"
"    }\n"
"}\n"
"namespace eval toggle {\n"
"    proc tag_all  { id } { return \"#tgl${id}\" }\n"
"    proc tag_box  { id } { return \"#tgl${id}_box\" }\n"
"    proc tag_knob { id } { return \"#tgl${id}_kn\" }\n"
"    proc draw_knob { c id color x y w h zoom } {\n"
"        set t [tag_knob $id]\n"
"        set ta [tag_all $id]\n"
"        set xpad [expr floor($w * 0.1)]\n"
"        set ypad [expr floor($h * 0.1)]\n"
"        if {$xpad > 16} { set xpad 16 }\n"
"        if {$ypad > 16} { set ypad 16 }\n"
"        if {$zoom == 1} {set corr 1} {set corr -1}\n"
"        set x0 [expr $x + $xpad + $corr]\n"
"        set y0 [expr $y + $ypad + $corr]\n"
"        set x1 [expr $x + $w - $xpad]\n"
"        set y1 [expr $y + $h - $ypad]\n"
"        set lw [expr 1 + $zoom]\n"
"        if {$w>30} {set lw [expr $lw + $xpad*0.5]}\n"
"        $c create line $x0 $y0 $x1 $y1 -fill $color -width $lw -capstyle butt -tags [list $t $ta]\n"
"        $c create line $x0 $y1 $x1 $y0 -fill $color -width $lw -capstyle butt -tags [list $t $ta]\n"
"    }\n"
"    proc create { cnv model id x y w h zoom value out_color fill_color knob_color } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set ta [tag_all $id]\n"
"        set tb [tag_box $id]\n"
"        # draw box\n"
"        $c create rectangle $x $y [expr $x+$w] [expr $y+$h] \\\n"
"            -fill $fill_color -outline $out_color -width $zoom -tags [list $ta $tb]\n"
"        if { $value } { draw_knob $c $id $knob_color $x $y $w $h $zoom }\n"
"    }\n"
"    proc update { cnv model id zoom value out_color fill_color knob_color } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set tb [tag_box $id]\n"
"        # update box\n"
"        $c itemconfigure $tb -fill $fill_color -outline $out_color\n"
"        lassign [$c coords $tb] x0 y0 x1 y1\n"
"        set w [expr $x1-$x0]\n"
"        set h [expr $y1-$y0]\n"
"        $c delete [tag_knob $id]\n"
"        if { $value > 0 } { draw_knob $c $id $knob_color $x0 $y0 $w $h $zoom }\n"
"    }\n"
"    proc erase { cnv model id } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        $c delete [tag_all $id]\n"
"    }\n"
"}\n"
"namespace eval slider {\n"
"    proc tag_all  { id } { return \"#sl${id}\" }\n"
"    proc tag_box  { id } { return \"#sl${id}_box\" }\n"
"    proc tag_fill { id } { return \"#sl${id}_fill\" }\n"
"    proc tag_knob { id } { return \"#sl${id}_kn\" }\n"
"    proc tag_min { id } { return \"#sl${id}_min\" }\n"
"    proc tag_max { id } { return \"#sl${id}_max\" }\n"
"    proc tag_value { id } { return \"#sl${id}_val\" }\n"
"    proc minmax_font { zoom } { return \"Helvetica [expr $zoom*8]\" }\n"
"    proc knob_xpos { x w pos zoom } {\n"
"        # keep in sync with knob width!\n"
"        if { $zoom > 1 } {\n"
"            return [expr (($w-$zoom)*$pos)+$x+($zoom/2)]\n"
"        } {\n"
"            return [expr (($w-1)*$pos)+$x+1]\n"
"        }\n"
"    }\n"
"    proc hcreate { cnv model id x y w h zoom pos value min max out_color fill_color knob_color } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set ta [tag_all $id]\n"
"        set tb [tag_box $id]\n"
"        set tf [tag_fill $id]\n"
"        set tkn [tag_knob $id]\n"
"        set tmin [tag_min $id]\n"
"        set tmax [tag_max $id]\n"
"        set tval [tag_value $id]\n"
"        # draw fill\n"
"        $c create rectangle $x $y [expr $x+$w] [expr $y+$h] \\\n"
"            -fill $fill_color -outline {} -width $zoom -tags [list $ta $tf]\n"
"        # draw min/max\n"
"        $c create text [expr $x+2] [expr $y+($h*0.5)] -text \"$min\" \\\n"
"            -fill $out_color -font [minmax_font $zoom] -justify left\\\n"
"            -anchor w -tags [list $ta $tmin]\n"
"        $c create text [expr $x+$w-2] [expr $y+($h*0.5)] -text \"$max\" \\\n"
"            -fill $out_color -font [minmax_font $zoom] -justify right \\\n"
"            -anchor e -tags [list $ta $tmax]\n"
"        # draw value\n"
"        $c create text [expr $x+($w*0.5)] [expr $y+($h*0.5)] -text \"$value\" \\\n"
"            -fill $out_color -font [minmax_font $zoom] -justify center \\\n"
"            -anchor center -tags [list $ta $tval]\n"
"        # draw knob\n"
"        set kx [knob_xpos $x $w $pos $zoom]\n"
"        set ky0 [expr $y+1]\n"
"        set ky1 [expr $y+$h-0.5]\n"
"        $c create line $kx $ky0 $kx $ky1 \\\n"
"            -fill $knob_color -width [expr 2*$zoom] -tags [list $ta $tkn]\n"
"        # draw box\n"
"        $c create rectangle $x $y [expr $x+$w] [expr $y+$h] \\\n"
"            -fill {} -outline $out_color -width $zoom -tags [list $ta $tb]\n"
"    }\n"
"    proc hupdate { cnv model id zoom pos value min max out_color fill_color knob_color } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set tb [tag_box $id]\n"
"        set tf [tag_fill $id]\n"
"        set tmin [tag_min $id]\n"
"        set tmax [tag_max $id]\n"
"        set tval [tag_value $id]\n"
"        set tkn [tag_knob $id]\n"
"        # update box\n"
"        $c itemconfigure $tb -outline $out_color\n"
"        $c itemconfigure $tf -fill $fill_color\n"
"        # update labels\n"
"        $c itemconfigure $tmin -fill $out_color -text \"$min\"\n"
"        $c itemconfigure $tmax -fill $out_color -text \"$max\"\n"
"        # update value\n"
"        $c itemconfigure $tval -fill $out_color -text \"$value\"\n"
"        lassign [$c coords $tb] x0 y0 x1 y1\n"
"        set w [expr $x1-$x0]\n"
"        set x [knob_xpos $x0 $w $pos $zoom]\n"
"        # update knob\n"
"        lassign [$c coords $tkn] x0 y0 x1 y1\n"
"        $c coords $tkn $x $y0 $x $y1\n"
"        $c itemconfigure $tkn -fill $knob_color\n"
"    }\n"
"    proc erase { cnv model id } {\n"
"        set ta [tag_all $id]\n"
"        ::nui::item_erase $cnv $model $ta\n"
"    }\n"
"    proc move  { cnv model id x y } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set tb [tag_box $id]\n"
"        set tkn [tag_knob $id]\n"
"        lassign [$c coords $tb] x0 y0 x1 y1\n"
"        set w [expr $x1-$x0]\n"
"        set h [expr $y1-$y0]\n"
"        $c coords $tb $x $y [expr $x+$w] [expr $y+$h]\n"
"        set dx [expr $x0-$x]\n"
"        set dy [expr $y0-$y]\n"
"        lassign [$c coords $tkn] x0 y0 x1 y1\n"
"        $c coords $tkn [expr $x+$dx] [expr $y+$dy]\n"
"    }\n"
"}\n"
"namespace eval bar {\n"
"    proc tag  { id } { return \"#bar${id}\" }\n"
"    proc hcreate { cnv model id x y w h pos fill_color } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set t [tag $id]\n"
"        set w [expr $pos*$w]\n"
"        $c create rectangle $x $y [expr $x+$w] [expr $y+$h] \\\n"
"            -fill $fill_color -outline $fill_color -width 1 -tags $t\n"
"    }\n"
"    proc hupdate { cnv model id w h pos fill_color } {\n"
"        set c [::nui::widget_canvas $cnv $model]\n"
"        set t [tag $id]\n"
"        $c itemconfigure $t -fill $fill_color -outline $fill_color\n"
"        lassign [$c coords $t] x0 y0 x1 y1\n"
"        set x1 [expr $x0 + $w*$pos]\n"
"        $c coords $t $x0 $y0 $x1 $y1\n"
"    }\n"
"}\n"
"}\n"
;
#endif
// clang-format on
