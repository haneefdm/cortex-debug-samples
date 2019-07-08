#!/usr/bin/env bash
SOURCE_DIR='J:/VSCode/MIEngine/bin/Desktop.Debug'

declare -a srcdirs=(
    # Primary machine where build actually happens
    "$SOURCE_DIR"
    # my second windows machine
    "${SOURCE_DIR/#J:/V:}"
    # My mac
    "${SOURCE_DIR/#J://Volumes/J}"
    # My linux
    "${SOURCE_DIR/#J://media/myxps0-j}"
)

#( IFS=$'\n'; echo "${srcdirs[*]}" ) ; exit 0

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
    if [[ ! -d "$dst" ]]; then
        if [[ "$dst" == "$dst1" ]]; then
            echo "Destination directory '$dst' does not exist"
            exit 1
        fi
        echo "Skipping destination dir '$dst'"
        continue
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

    for f in "${files[@]}" ; do
        echo "Copying '$src/$f' ..."
        cp -p "$src/$f" "$dst"
        [[ $? == 0 ]] || { echo "Failed!!!" ; exit 1 ; }
    done
    echo "Listing of '$dst'"
    ls -lrt "$dst"
    echo ======================================================================
done
