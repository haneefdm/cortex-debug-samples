# Design thoughts for full disassembly support

## Requirements

In the requirements below, **none** of them are currently possible with any VSCode debugger. Even with Cortex-Debug RE#1 is not fully met -- not intermixed source info. All of the following imply a debug session.

1. Display disassembly with any original source code intermixed.
2. Track the call-stack window's current frame if any
3. Show the current stopped location (if any)
4. Set/clear breakpoints in disassembly window
5. Do stepi/nexti using the same debug buttons/commands as step/next. No new UI elements will be needed or desired. If the active editor is the disassembly window, then a stepi/nexti will happen. After a stepi/nexti, we would want the active editor to remain as is and not switch to actual source code. Step-out and continue will work normally ie. not dependent on the active editor. Would be nice if Step-out worked like stepi/nexti.
6. Perform lazy/smart loading of disassembly. Be performant with response time measured under 100ms.
7. Perform smart scrolling -- support several instructions before and after the current viewport. Ideally, this should be 1-3 view-ports before and after
8. Do appropriate color highlighting to clearly show address, instructions and source code. Even source code syntax highlighting would be nice

## Background

There are three major parts to the overall functionality

- __Debug Adapter__: Cortex-Debug or MIEngine are debug adapters that support the Debug Adapter Protocol (DAP).
- __Debug Frontend__: Currently, that would be VSCode. It hosts the various debug windows (panels) like call-stack, variables, breakpoints, etc.
- __Debugger Extension__: This is a support module that provides the __Debug Frontend__ with the DAP and does other housekeeping frontend chores. Cortex-Debug (CD) and cpptools are example of this. When the user clicks on a particular frame, VSCode tries to open that source file.
- The DAP already does the following:

  - Whenever the debuggee (target) is halted for any reason (breakpoint, pause, exception, etc.). It notifies and provides the frontend with the current thread/frame information.
  - Foreach item in the frame, there is a source document/line-info associated with it. Or it is a NULL document.
  - The NULL document can be replaced with a URI that represents a disassembly window and location would be the address (program counter). This is what currently happens in Cortex-Debug (CD). cpptools has no equivalent (yet)!

## Disassembly window

- It is a single read-only editor window that hosts the disassembly window. There will be one such window per target process. Note that there can be multiple debug sessions going on in VSCode at the same time.
  - TODO: However, we want to reuse disassembly windows and not create new one for every launch. One way to do this is to use the executable (elf-file) as part of the URI + a session id.
- Window Creation: The window is created when the user clicks on a particular stack frame if such a URI is not already there
- The debug extension (frontend) tracks the active editor and notifies the debug adapter if the current editor is the disassembly window or something else. The editor itself can do this as well. Will revisit responsibility later
- Be aware of when the target is running, stopped or exited/session-ended
- The internal design of the model (data) for the editor requires that we keep zero or more spans of disassembly information. ie., you can have gaps. Where data is present, it has to be marked as dirty when a debug-session ends and until the next session starts when all disassembly info can be deleted. However if a session is not active+stopped, then no further instructions are loaded. User may not be allowed to scroll past gaps.

## Deficiencies, show stoppers

There are some deficiencies that are beyond the control of an extension or DA. Some deficiencies can be fixed by the DA providing custom-requests and maintaining some additional state information.

- VSCode: **There is no event generated when the user changes focus in the call-stack window**
- DA: There is no good way to know when to do a stepi/nexti. With CD, this is done by tracking the active editor.
- VSCode: There is no way to tell VSCode that you can have a valid source file as well as an address for disassembly. Not even sure if we can setup a trampoline to forward source code load requests from VSCode to the actual editor responsible.
  - This means that disassembly would be modal? Ie., the DA has to tell VSCode if a given frame should use source or disassembly - based on the active editor?!?
  - If a call-stack window event is available, then technically, we can always display the disassembly but the debug gutter would not show the current address marker. We can have an alternate way by highlighting the whole line/instruction. You should still be able to manipulate breakpoints.
- If the trampoline idea works, quite a few of our problems are solved, albeit in a weird way. May affect UX

## Requirements research
