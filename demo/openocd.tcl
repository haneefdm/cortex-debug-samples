#debug_level 3
set ENABLE_CM0 0
set ENABLE_ACQUIRE 0
source [find interface/kitprog3.cfg];
source [find target/psoc6.cfg];
# ${TARGET}.cm4 configure -rtos auto

# puts "Haneef: MyTarget is $_TARGETNAME"

if {0} {
    foreach t [target names] {
        puts "Haneef Target: $t"
    }

    set junk_port 60000
    set my_cpu "psoc6.cpu.cm4";  # This is what I want to debug
    foreach t [target names] {
        if {[string compare $t $my_cpu] != 0} {
            $t configure -gdb-port $junk_port
            puts "My Msg: CPU $t should now using gdb port $junk_port"
            incr junk_port
        }
    }
}

#init
#reset init
