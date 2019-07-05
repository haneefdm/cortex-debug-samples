# PSoC6 setup instructions for Cortex-Debug

1. Make sure your board is updated with latest firmware and set to the appropriate mode for OpenOCD. MTB 2.0 has latest. MTB 1.1 may have it as well
2. Install Cortex-Debug 0.3.1 or higher
3. Make sure you have the latest OpenOCD from MTB 2.0 build. Or download [from here](https://drive.google.com/open?id=1fxMy1w-5lRPW1otD7BurX3ukoxdtVCB_)
4. In `settings.json` copy the following lines. You can put this in your workspace `.vscode` directory or in your [global settings](https://code.visualstudio.com/docs/getstarted/settings#_settings-file-locations). Global settings is preferable since they are user and OS specific unless you are working on multiple projects that require different settings

    ```javascript
    // path where objdump and gdb can be found
    "cortex-debug.armToolchainPath": "/Applications/ModusToolbox_2.0/tools/gcc-7.2.1-1.0/bin/",
    // gdb-server-paths
    "cortex-debug.openocdPath": "/Applications/ModusToolbox_2.0/tools/openocd-2.2/bin/openocd",
    "cortex-debug.JLinkGDBServerPath": "/Applications/SEGGER/JLink_V644a/JLinkGDBServerCLExe",
    ```

5. In `.vscode/launch.json`, have the following configurations. Make sure you edit the `executable` entries below and that all path names are valid for your environment.

    ```javascript
    {
        "name": "Launch PSoC6 CM4 (OpenOCD)",
        "type": "cortex-debug",
        "request": "launch",
        "cwd": "${workspaceRoot}",
        "executable": "BlinkyLED_mainapp/Debug/BlinkyLED_mainapp_final.elf",
        "servertype": "openocd",
        "searchDir": [ 
            "${workspaceRoot}",
            "/Applications/ModusToolbox_2.0/tools/openocd-2.2/scripts/",
        ],
        "configFiles": [
            "openocd.tcl"
        ],
        "preLaunchCommands": [
            "set mem inaccessible-by-default off",
        ],
        "postLaunchCommands": [
            "monitor reset run",
            "monitor sleep 200",
            "monitor psoc6 reset_halt sysresetreq"
        ],
        "postRestartCommands": [
            "monitor psoc6 reset_halt sysresetreq",
            /*
            // Following two commands are needed to get gdb and openocd and HW all in sync.
            // Or, execution context (PC, stack, registers, etc.) look like they are from before reset.
            // The stepi, is a pretend instruction that does not actually do a stepi, but MUST be done
            // Its a documented workaround in openocd. Do a 'monitor help' to see more info
            */
            "monitor gdb_sync",
            "stepi"
        ],
        // svdFiles are optional can be very large. You can also set 'toolchainPath' and 'serverpath`
        // in an OS specific way here.
        "osx": {
            "svdFile": "/Applications/ModusToolbox_2.0/libraries/udd-1.1/udd/devices/MXS40/PSoC6ABLE2/studio/svd/psoc6_01.svd",
        },
        "windows": {
            "svdFile": "${env:USERPROFILE}/ModusToolbox_2.0/libraries/udd-1.1/udd/devices/MXS40/PSoC6ABLE2/studio/svd/psoc6_01.svd",
        },
        "linux": {
            "svdFile": "${env:HOME}/ModusToolbox_2.0/libraries/udd-1.1/udd/devices/MXS40/PSoC6ABLE2/studio/svd/psoc6_01.svd",
        },
        "runToMain": true,          // if true, program will halt at main. Not used for a restart
        "preLaunchTask": "",        // Set this to run a task from tasks.json before starting a debug session
        "showDevDebugOutput": false,// Shows output of GDB, helpful when something is not working right
    },
    // When using 'attach', make sure your program is running on the board and that your executable matches
    // the image in the chip exactly, or else strange things can happen with breakpoint, variables, etc.
    {
        "name": "Attach PSoC6 CM4 (OpenOCD)",
        "type": "cortex-debug",
        "request": "attach",
        "cwd": "${workspaceRoot}",
        "executable": "BlinkyLED_mainapp/Debug/BlinkyLED_mainapp_final.elf",
        "servertype": "openocd",
        "searchDir": [ 
            "${workspaceRoot}",
            "/Applications/ModusToolbox_2.0/tools/openocd-2.2/scripts/",
        ],
        "configFiles": [
            "openocd.tcl"
        ],
        "preAttachCommands": [
            "set mem inaccessible-by-default off",
        ],
        "postRestartCommands": [
            "monitor psoc6 reset_halt sysresetreq",
            "monitor gdb_sync",
            "stepi"
        ],
        // svdFiles are optional can be very large. You can also set 'toolchainPath' and 'serverpath`
        // in an OS specific way here.
        "osx": {
            "svdFile": "/Applications/ModusToolbox_2.0/libraries/udd-1.1/udd/devices/MXS40/PSoC6ABLE2/studio/svd/psoc6_01.svd",
        },
        "windows": {
            "svdFile": "${env:USERPROFILE}/ModusToolbox_2.0/libraries/udd-1.1/udd/devices/MXS40/PSoC6ABLE2/studio/svd/psoc6_01.svd",
        },
        "linux": {
            "svdFile": "${env:HOME}/ModusToolbox_2.0/libraries/udd-1.1/udd/devices/MXS40/PSoC6ABLE2/studio/svd/psoc6_01.svd",
        },
        "showDevDebugOutput": false,// Shows output of GDB, helpful when something is not working right
    },
    ```

6. In your workspace directory, create a file called `openocd.tcl` with the following contents

    ```tcl
    set ENABLE_CM0 0
    # Following line is only needed for attach but doesn't hurt for launch
    set ENABLE_ACQUIRE 0
    source [find interface/kitprog3.cfg];
    source [find target/psoc6.cfg];
    # uncomment below for RTOS support. See http://openocd.org/doc/html/GDB-and-OpenOCD.html
    #${TARGET}.cm4 configure -rtos auto
    ```

7. Besides the 'Debug Console', look in the Output tab next to it (select the 'Adapter Output` from the dropdown) to see the output from the gdb-server. If the OpenOCD server does not start properly, you will see some messages here.

![Example error](./images/openocd-error.jpg)
