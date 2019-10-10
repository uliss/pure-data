# PATCHER MOUSE MOTION
proc eobj_canvas_motion {patcher val} {
    set rx [winfo rootx $patcher]
    set ry [winfo rooty $patcher]
    set x  [winfo pointerx .]
    set y  [winfo pointery .]
    pdtk_canvas_motion $patcher [expr $x - $rx] [expr $y - $ry] $val
}

# PATCHER MOUSE DOWN
proc eobj_canvas_down {patcher val} {
    set rx [winfo rootx $patcher]
    set ry [winfo rooty $patcher]
    set x  [winfo pointerx .]
    set y  [winfo pointery .]
    pdtk_canvas_mouse $patcher [expr $x - $rx] [expr $y - $ry] 0 $val
}

# PATCHER MOUSE UP
proc eobj_canvas_up {patcher} {
    set rx [winfo rootx $patcher]
    set ry [winfo rooty $patcher]
    set x  [winfo pointerx .]
    set y  [winfo pointery .]
    pdtk_canvas_mouseup $patcher [expr $x - $rx] [expr $y - $ry] 0
}

# PATCHER MOUSE RIGHT
proc eobj_canvas_right {patcher} {
    set rx [winfo rootx $patcher]
    set ry [winfo rooty $patcher]
    set x  [winfo pointerx .]
    set y  [winfo pointery .]
    pdtk_canvas_rightclick $patcher [expr $x - $rx] [expr $y - $ry] 0
}

# OBJECT SAVE FILE
proc eobj_saveas {name initialfile initialdir} {
    if { ! [file isdirectory $initialdir]} {set initialdir $::env(HOME)}
    set filename [tk_getSaveFile -initialfile $initialfile -initialdir $initialdir -filetypes $::filetypes]
    if {$filename eq ""} { return }

    set extension [file extension $filename]
    set oldfilename $filename

    if {$filename ne $oldfilename && [file exists $filename]} {
        set answer [tk_messageBox -type okcancel -icon question -default cancel-message [_ "$filename" already exists. Do you want to replace it?]]
        if {$answer eq "cancel"} { return }
    }
    set dirname [file dirname $filename]
    set basename [file tail $filename]
    pdsend "$name eobjwriteto [enquote_path $dirname/$basename]"
    set ::filenewdir $dirname
}

# OBJECT OPEN FILE
proc eobj_openfrom {name} {
    if { ! [file isdirectory $::filenewdir]} {
    set ::filenewdir [file normalize $::env(HOME)]
    }
    set files [tk_getOpenFile -multiple false -initialdir $::fileopendir]
    pdsend "$name eobjreadfrom [enquote_path $files]"
}

# RGBA TO HEX
proc eobj_rgba_to_hex {red green blue alpha} {
    set nR [expr int( $red * 65025 )]
    set nG [expr int( $green * 65025 )]
    set nB [expr int( $blue * 65025 )]
    set col [format {%4.4x} $nR]
    append col [format {%4.4x} $nG]
    append col [format {%4.4x} $nB]
    return #$col
}

# RGB int list to RGB float list
proc eobj_rgb_int_to_float {red green blue} {
    set nR [expr ( $red / 65025. )]
    set nG [expr ( $green / 65025. )]
    set nB [expr ( $blue / 65025. )]
    if {$nR > 1.} {set nR 1.}
    if {$nG > 1.} {set nG 1.}
    if {$nB > 1.} {set nB 1.}
    return [concat $nR $nG $nB]
}

proc ceammc_create_label_font_bold {font_name} {
    set font [ttk::style lookup TLabel -font]
    set family [font configure $font -family]
    set size [font configure $font -size]
    set slant [font configure $font -slant]
    set underline [font configure TkDefaultFont -underline]
    return [font create $font_name -family $family -size $size -weight bold -slant $slant -underline $underline]
}

proc ceammc_category_icon {state} {
    if {$state ne 0} {
        return ceammc_image_category_opened
    } {
        return ceammc_image_category_closed
    }
}

proc ceammc_category_apply {id var_name_state controls} {
    global $var_name_state
    set v [expr $$var_name_state]
    $id configure -image [ceammc_category_icon $v]

    foreach w $controls {
        if {$v eq 0 } {
            grid remove $w
        } {
            grid config $w
        }
    }
}

proc ceammc_category_toggle {id var_name_state controls} {
    global $var_name_state
    set v [expr $$var_name_state]
    if {$v ne 0} { set $var_name_state 0 } { set $var_name_state 1 }

    ceammc_category_apply $id $var_name_state $controls
}

# create images
if { $::tcl_version >= 8.6 } {
    image create photo ceammc_image_category_opened -width 18 -height 18 \
        -data "iVBORw0KGgoAAAANSUhEUgAAABIAAAASCAQAAAD8x0bcAAAAQklEQVR4AWMYDoAFnYcJNBnuMFjDebYMtxk0MBVJMtxg+MxgA1XyBciTBLMxlQElbfAoQShDKMGjDKYErzIgHFEAAGLzEOwIrN0jAAAAAElFTkSuQmCC"
    image create photo ceammc_image_category_closed -width 18 -height 18 \
        -data "iVBORw0KGgoAAAANSUhEUgAAABIAAAASCAQAAAD8x0bcAAAAPUlEQVR4AWMY9ICNoZCBlZAiH4b/DGsIK8sjTlkBccoqgcqW41fCy3CE4Q9DKO2UIIArw3egEoJAkmGIAABqKxDmokl7sAAAAABJRU5ErkJggg=="
} else {
    image create photo ceammc_image_category_opened -width 18 -height 18 \
        -data "R0lGODlhEgASAPAAAAAAAAAAACH5BAEAAAAAIf8LSW1hZ2VNYWdpY2sOZ2FtbWE9MC40NTQ1NDUALAAAAAASABIAAAIahI+py+0Po2RB1RauyY8D32UaBE7miabqmhQAOw=="
    image create photo ceammc_image_category_closed -width 18 -height 18 \
        -data "R0lGODlhEgASAPAAAAAAAAAAACH5BAEAAAAAIf8LSW1hZ2VNYWdpY2sOZ2FtbWE9MC40NTQ1NDUALAAAAAASABIAAAIYhI+py+0PowpBHmoNzjt2+D2hmJXmiToFADs="
}

# create font for categories in dialog
ceammc_create_label_font_bold CICMCategoryFont

# show tooltips
if { [catch {package require tooltip} ] } {
    proc ceammc_tooltip {id msg} {}
} {
    proc ceammc_tooltip {id msg} {
        tooltip::tooltip $id $msg
    }
}

proc ceammc_fix_macos_state {n} { if { $n > 256 } { return [expr $n & 0xFF ] } { return $n } }

proc ceammc_fix_win_state {n} {
# fix offset
    incr n -32
# hangle ALT modifier
    if { $n >= 131072 } {
        incr n -131072
        set n [expr $n | 16]
    }
    return $n
}

proc ceammc_fix_x11_state {n} {
}

proc ceammc_send_motion {obj x y mod} {
    switch -- $::windowingsystem {
        "aqua" {
            # disable mouse dragging for buttons other then first
            if { $mod < 512 } { pdsend "$obj mousemove $x $y [ceammc_fix_macos_state $mod]" }
        } "default" {
            pdsend "$obj mousemove $x $y $mod"
        }
    }
}

proc ceammc_bind_mouse_down {id obj} {
    switch -- $::windowingsystem {
        "win32" {
            bind $id <ButtonPress-1> [subst -nocommands {+pdsend "$obj mousedown %x %y %X %Y [ceammc_fix_win_state %s]"}]
        } "default" {
            bind $id <ButtonPress-1> [subst {+pdsend "$obj mousedown %x %y %X %Y %s"}]
        }
    }
}

# sends #obj mouseup X Y MOD
proc ceammc_bind_mouse_up {id obj} {
    switch -- $::windowingsystem {
        "aqua" {
            bind $id <ButtonRelease-1> [subst -nocommands {+pdsend "$obj mouseup %x %y [ceammc_fix_macos_state %s]"}]
        } "win32" {
            bind $id <ButtonRelease-1> [subst -nocommands {+pdsend "$obj mouseup %x %y [ceammc_fix_win_state %s]"}]
        } "default" {
            bind $id <ButtonRelease-1> [subst {+pdsend "$obj mouseup %x %y %s"}]
        }
    }
}

# sends #obj mousemove X Y MOD
proc ceammc_bind_mouse_move {id obj} { bind $id <Motion> [subst {+ceammc_send_motion $obj %x %y %s}] }
proc ceammc_bind_mouse_enter {id obj} { bind $id <Enter> [subst {+pdsend "$obj mouseenter"}] }
proc ceammc_bind_mouse_leave {id obj} { bind $id <Leave> [subst {+pdsend "$obj mouseleave"}] }
proc ceammc_bind_mouse_double_click {id obj} { bind $id <Double-Button-1> [subst {+pdsend "$obj dblclick %x %y %s"}] }

# sends #obj mouseup X Y ABSX ABSY MOD
proc ceammc_bind_mouse_right_click {id obj} {
    switch -- $::windowingsystem {
        "aqua" {
            bind $id <ButtonPress-2> [subst {+pdsend "$obj rightclick %x %y %X %Y %s"}]
            bind $id <Control-ButtonPress-1> [subst {+pdsend "$obj rightclick %x %y %X %Y %s"}]
        } "default" {
            bind $id <ButtonPress-3> [subst {+pdsend "$obj rightclick %x %y %X %Y %s"}]
        }
    }
}

# sends #obj mouseup X Y DELTA MOD
proc ceammc_bind_mouse_wheel {id obj} {
    switch -- $::windowingsystem {
        "win32" {
            bind $id <MouseWheel> [subst -nocommands {+pdsend "$obj mousewheel %x %y [expr %%D / 120.0] [ceammc_fix_win_state %s]"}]
        } "default" {
            bind $id <MouseWheel> [subst {+pdsend "$obj mousewheel %x %y %%D %s"}]
        }
    }
}
