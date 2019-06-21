# PSoC6 setup instructions for Cortex-Debug


1. Install Cortex-Debug 0.3.1 or higher
2. Make sure you have the latest OpenOCD from MTB 2.0 build. Or download from here <https://drive.google.com/open?id=1fxMy1w-5lRPW1otD7BurX3ukoxdtVCB_>
3. in `settings.json` copy the following lines. You can put this in your workspace .vscode directory or in your global settings. Global settings is preferable since they are user and OS specific

    ```javascript
    // path where objdump and gdb can be found
    "cortex-debug.armToolchainPath": "/Applications/ModusToolbox_2.0/tools/gcc-7.2.1-1.0/bin/",
    // gdb-server-paths
    "cortex-debug.openocdPath": "/Applications/ModusToolbox_2.0/tools/openocd-2.2/bin/openocd",
    "cortex-debug.JLinkGDBServerPath": "/Applications/SEGGER/JLink_V644a/JLinkGDBServerCLExe",
    ```

4. In `.vscode/launch.json`, have the following configuration. Make sure you edit the `executable` entry below and all path names make are valid for your environment.

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
            /*
            // Following three commands are needed because Cortex-Debug is hardcoded to do a
            // `monitor reset halt`. Creates a problem for multi core systems like
            // PSoC6, so this is a workaround. Normally, only a sysresetreq is needed for PSoc6
            */
            "monitor reset run",
            "monitor sleep 200",
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
    ```

5. In your workspace directory, create a file called `openocd.tcl` with the following contents

    ```tcl
    set ENABLE_CM0 0
    source [find interface/kitprog3.cfg];
    source [find target/psoc6.cfg];
    ```

6. Besides the 'Debug Console', look in the Output tab next to it (select the 'Adapter Output` from the dropdown) to see the output from the gdb-server. If the OpenOCD server does not start properly, you will see some messages here.
