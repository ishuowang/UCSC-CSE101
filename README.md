# Congrats⚡️
I got an **__`A`__** in this course, all the source code and quiz in this course will published at this repo.

# How to use?

Below shows the file structure, the folder **`pa[x]/backup`** (x specific x_th project assignment) contains the complete code with grading_sctipt tested.

```
.
├── C/                  # provided at Example: https://classes.soe.ucsc.edu/cse101/Winter22
├── C++/                # provided at Example: https://classes.soe.ucsc.edu/cse101/Winter22
├── pa1/                # pa[x]: completed project assignment
├── pa2/                
├── pa3/
├── pa4/
├── pa5/
├── pa6/
├── pa7/
├── pa8/
├── Pseudo-Code/        # provided at Example: https://classes.soe.ucsc.edu/cse101/Winter22
├── README.md
└── Resource/           # .pdf files: assignment description 
```

Gradding script is posted at this [repository](https://github.com/agavgavi/cse101-pt.w22.git).

# Quick start

To test the code by yourself, please follow the instruction following:

1. clone this repository

```
git clone git@github.com:21wang12/UCSC-CSE101.git
```
2. change your work directory to specific pa, please change `[x]` whith the number of pa you want to.

```sh
cd ./UCSC-CSE101/
cd ./pa[x]/         
```

take pa1 as example

```sh
cd ./UCSC-CSE101/
cd ./pa1/ 
```

3. download and run gradding script, please change `[x]` whith the number of pa you want to.

```sh
wget https://raw.githubusercontent.com/agavgavi/cse101-pt.w22/main/pa[x]/pa[x].sh -o pa[x].sh
chmod 777 ./pa[x].sh
./pa[x].sh
```

also, take pa1 as example

```sh
wget https://raw.githubusercontent.com/agavgavi/cse101-pt.w22/main/pa1/pa1.sh -o pa1.sh
chmod 777 ./pa1.sh
./pa1.sh
```

4. submit & enjoy your project assignment😋.



# Useful infomation(option)

## Download example code directorcy without hierarchy

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

## Configure Debug mode in VSCode

1. Create a `launch.json` file under current work directory `.vscode/` folder and edit it like this
```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "pa2",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}", 
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

Here is the screenshot shows the debug mode, this really bring more convience for debugging.

<img width="1143" alt="image" src="https://user-images.githubusercontent.com/38482259/159444058-e8d79f69-e2d3-4f58-a2e6-3298a5584bb2.png">


