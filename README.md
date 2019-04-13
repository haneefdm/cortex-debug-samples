# cortex-debug-samples

Repo for storing misc. stuff related to corted-debug testing

File cortex-debug-0.2.4.vsix is my latest cortex-debug extension that contains certain fixes. Will keep this available until my changes are officially merged into <https://github.com/Marus/cortex-debug>

See: <https://github.com/Marus/cortex-debug/pull/151>

## Install from vsix
* Download the vsix file
* Select the Extension Viewlet on left edge of VSCode where you see all the extensions
* On top right, click on the '...' and select "Install from VSIX" and select the file just downloaded
* Or, from the command line, you can do

    `code --install-extension filename.vsix`

## Other stuff
Directory 'demo' contains a small application for PSoC6. Interesting bits are in demo/.vscode directory. You will have to modify path names in launch.json, setting.json, etc.

