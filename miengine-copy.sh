#!/usr/bin/env bash
cppextdir='ms-vscode.cpptools-0.24.0-insiders3'
declare -a srcdirs=(
    'J:/VSCode/MIEngine/bin/Desktop.Debug'
    'V:/VSCode/MIEngine/bin/Desktop.Debug'
    'C:/Users/hdm/vscode/MIEngine/bin/Desktop.Debug'
    '/Volumes/hdm/vscode/MIEngine/bin/Desktop.Debug'
    '/media/myxps0-j/VSCode/MIEngine/bin/Desktop.Debug'
)

src=
for d in "${srcdirs[@]}" ; do
    if [[ -d "$d" ]]; then
	src="$d"
	echo "Using source dir '$src'"
	break
    fi
    echo "Skipping source dir '$d' not found"
done
[[ "$src" == "" ]] && { echo "Error: No suitable source dir found." ; exit 1 ; }

dllExt='dll.mdb'
exeExt='exe.mdb'
if [[ ($OSTYPE == 'cygwin') || ($OSTYPE == 'win32') ]]; then
    dllExt='pdb'
    exeExt='pdb'
    export HOME="${USERPROFILE//\\//}"
fi

dst="$HOME/.vscode/extensions/$cppextdir/debugAdapters/bin"
dst2="$HOME/.vscode-oss-dev/extensions/$cppextdir/debugAdapters/bin"
if [[ ! -d "$dst" ]]; then
    echo "Destination directory '$dst' does not exist"
    exit 1
else
    echo "Destination dir '$dst'"
fi

if [[ ! -d "${dst}.bak" ]]; then
    echo "Making a backup of '$dst'"
    cp -r "$dst" "${dst}.bak"
    [[ $? == 0 ]] || { echo Failed to create backup ; exit 1 ; }
else
    echo "Note: Backup '${dst}.bak' already exists..."
fi

declare -a files=(
    "Microsoft.MICore.dll"
    "Microsoft.MICore.XmlSerializers.dll"
    "Microsoft.MIDebugEngine.dll"
    "vscode/OpenDebugAD7.exe"
    "vscode/Microsoft.DebugEngineHost.dll"
    "vscode/Microsoft.VisualStudio.Shared.VSCodeDebugProtocol.dll"
    "Microsoft.MICore.${dllExt}"
    "Microsoft.MIDebugEngine.${dllExt}"
    "vscode/OpenDebugAD7.${exeExt}"
    "vscode/Microsoft.DebugEngineHost.${dllExt}"
)

for f in "${files[@]}" ; do
    echo "Copying '$src/$f' ..."
    cp -p "$src/$f" "$dst"
    [[ $? == 0 ]] || { echo "Failed!!!" ; exit 1 ; }
    if [[ -d "$dst2" ]]; then
	cp -p "$src/$f" "$dst2"
	[[ $? == 0 ]] || { echo "Failed!!!" ; exit 1 ; }
    fi
done

echo "Listing of '$dst'"
ls -lrt "$dst"
[[ -d "$dst2" ]] && echo "Listing of '$dst2'" && ls -lrt "$dst2"
