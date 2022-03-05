# Download example code directorcy without hierarchy

Use blow command to get the PA you want to download

```bash
# Please specify x to which pa you want to install, eg: x=2 will download pa2 
cd /cse101
wget -nH --cut-dirs=3 -e robots=off -r -R "index.html*,*.gif"  https://classes.soe.ucsc.edu/cse101/Winter22/Examples/pa<x>/

# To download pa1 in winter22(current term) please run this command
cd /cse101
wget -nH --cut-dirs=3 -e robots=off -r -R "index.html*,*.gif"  https://classes.soe.ucsc.edu/cse101/Winter22/Examples/pa1/

# To download pa1 in spring21(previous term) please run this command
cd /cse101
wget -nH --cut-dirs=3 -e robots=off -r -R "index.html*,*.gif"  https://classes.soe.ucsc.edu/cse101/Spring21/Examples/pa1/
```

# Configure Debug mode in VSCode

1. Create a `launch.json` file under current work directory `.vscode/` folder and edit it like this
```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "pa2",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}", // path to executable program.
            "args": ["in1","my-out1"],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
        }
    ]
}
```

2. In the Makefile under the specific Programming Assignment folder, add the -g option at the COMPILE line.
```Makefile
# Add -g parameter can create debug version
COMPILE        = gcc -std=c17 -Wall -c -g
```

3. Compile the source code with command `$ make`, and the program you want to debug with will be produced containning debug infromation.

4. In the VSCode editor, open the file you want to debug with(ie: in pa2, open the FindPath.c in the vscode editor, so `${fileDirname}/${fileBasenameNoExtension}` in `launch.json` can find the FindPath program that you want to debug with)

5. Click the `Run and Debug` button in the left column of VSCode, and click the start debuging button, then the program will be execute in debug mode.
