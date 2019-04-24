
#debug_level 3
set ENABLE_CM0 0
source [find interface/kitprog3.cfg];
source [find target/psoc6.cfg];
puts stderr {Started by VSCode};

# HDM: Following code is needed if you want to run 'init'. You cannot change the
# gdb_port after init. Since init is called automatically by OpenOCD, we do not
# need to run it here. THIS CODE SHOULD NOT EXIST
if {0} {
    # Hardcode gdb_port to 50000 to override the default 3333. We will not get
    # a chance to do it again
    set our_preferred_gdb_port 50000
    if { $ENABLE_CM0 != 0 } {
        incr our_preferred_gdb_port -1
        puts "HDM: Enable real port for debugging CM4: backup ${our_preferred_gdb_port} port by 1"
    }

    gdb_port $our_preferred_gdb_port
    puts -nonewline "HDM: Forcing gdb_port to " ; gdb_port

    # Disable the gdb_port function to become a no-op to prevent Cortex-Debug from
    # setting it after calling init will throw an exception and debugger wont start.
    # Thing is it may have been overridden by lines above but no way for us to know.
    # Would have been nice if [gdb_port] returned the current port rather than printing
    # to stdout
    rename gdb_port gdb_port_orig
    proc gdb_port {args} {
        global our_preferred_gdb_port
        if {[llength args] > 0} {
            puts -nonewline "HDM: gdb_port can't be changed after calling init. ignored. Current value = "
        }
        gdb_port_orig
        return $our_preferred_gdb_port
    }
}

#init
#reset init