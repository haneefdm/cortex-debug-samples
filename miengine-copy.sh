#!/usr/bin/env bash
REMOTE_DIR='V:/VSCode/MIEngine.dist/Desktop.Debug'
LOCAL_DIR='C:/Users/hdm/vscode/MIEngine/bin/Desktop.Debug'

declare -a srcdirs=(
    "$LOCAL_DIR"
    "$REMOTE_DIR"
    "${REMOTE_DIR//V:/J:}"
    '/Volumes/J/VSCode/MIEngine.dist/Desktop.Debug'
    '/media/myxps0-j/VSCode/MIEngine.dist/Desktop.Debug'
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

if [[ "$src" == "$LOCAL_DIR" ]];then
    if [[ -d "$REMOTE_DIR" ]]; then
        rm -fr "$REMOTE_DIR"
        [[ $? == 0 ]] || { echo Failed to compeletel delete $REMOTE_DIR ; }
    fi
    echo "Copyying '$src' to '$REMOTE_DIR' ..."
    mkdir -p "$REMOTE_DIR"
    cp -fpr "$src"/*  "$REMOTE_DIR"
    [[ $? == 0 ]] || { echo Failed to copy to $REMOTE_DIR ; exit 1 ; }
fi

dllExt='dll.mdb'
exeExt='exe.mdb'
if [[ ($OSTYPE == 'cygwin') || ($OSTYPE == 'win32') ]]; then
    dllExt='pdb'
    exeExt='pdb'
    export HOME="${USERPROFILE//\\//}"
fi

# Find latest extension
exthome="$HOME/.vscode/extensions"
extdir=`ls -1rt "$exthome" | grep ms-vscode.cpptools | tail -1`
dst1="$exthome/$extdir/debugAdapters/bin"
dst2="${dst1//.vscode/.vscode-oss-dev}"
dst3="${dst1//.vscode/.vscode-insiders}"

declare -a dsts=("$dst1")
[[ -d "$dst2" ]] && dsts+=("$dst2")
[[ -d "$dst3" ]] && dsts+=("$dst3")

# (IFS=$'\n'; echo "${dsts[*]}")

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

for dst in "${dsts[@]}" ; do
    echo "Destination dir '$dst'"
    if [[ ! -d "${dst}.bak" ]]; then
        echo "Making a backup of '$dst'"
        cp -r "$dst" "${dst}.bak"
        [[ $? == 0 ]] || { echo Failed to create backup ; exit 1 ; }
    else
        echo "Note: Backup '${dst}.bak' already exists..."
    fi

    for f in "${files[@]}" ; do
        echo "Copying '$src/$f' ..."
        cp -p "$src/$f" "$dst"
        [[ $? == 0 ]] || { echo "Failed!!!" ; exit 1 ; }
    done
    echo "Listing of '$dst'"
    ls -lrt "$dst"
    echo ======================================================================
done
