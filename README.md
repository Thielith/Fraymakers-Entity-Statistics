# Fraymakers Entity Statistics
 Prints out statistics related to an Fraymakers Custom Content .entity file.

## Usage
Define the .entity file to be used with `(-f --file) [path/to/file.entity]`

If you want to output to a file, use the flags `(-o or --output) [path/to/save/output.txt]`

The program prints this information with `-h` if you ever forget.

## Libraries Used
- [Entity Extractor](https://github.com/Thielith/Fraymakers-Entity-Data-Extractor): For extracting the data from the .entity files
  - [jsoncpp](https://github.com/open-source-parsers/jsoncpp): For parsing the .entity files.
  - [mingw-w64-jsoncpp](https://aur.archlinux.org/packages/mingw-w64-jsoncpp): For compiling the Windows executable version of the program.

## Compiling the Stuff in the Repository
1. Follow the install instructions for the used libraries.
2. Pick your ~~poison~~ platform of choice below.

### Linux
1. Download source files.
    - If you want to make Windows executables, also install [mingw-w64-jsoncpp](https://aur.archlinux.org/packages/mingw-w64-jsoncpp). If you don't know how, just use `yay`
2. Run the included makefile.
    - Note:  It assumes you followed the instructions from the [Entity Extractor](https://github.com/Thielith/Fraymakers-Entity-Data-Extractor) library page and put the libraries and header stuff in `/usr/local/lib` and `/usr/local/include` respectivley.  If you didn't, then modify the paths in the `LOOK_HERE_TOO` makefile variable.
    - To make Windows executables, run `make windows`

### Windows (outdated, probably)
Setting up the right dependicies on Windows took me a long time so there will be unnecessary steps below if you're an experienced dev.
If these instructions fail, please create an issue about it.

1. Download source files.
2. Go to [MSYS2](https://www.msys2.org/) and follow the install guide to get the Windows C/C++ compilers.

#### Option 1:  VS Code
3. Get [VS Code](https://code.visualstudio.com/)
4. Install the C/C++ extension
5. With `main.cpp` selected, click the run button in the top right (looks like a > play button)

#### Option 2:  CMake
3. Install [CMake](https://cmake.org/)
4. Download [Ninja](https://ninja-build.org/) and put it somewhere safe
5. Add the following enviroment variables (User or System)
    - `CC` which points to `[/path/to/msys64]/ucrt64/bin/gcc.exe`
    - `CXX` which points to `[/path/to/msys64]/ucrt64/bin/g++.exe`
6. Add the following paths to the PATH enviroment variable (User or System)
    - `[/path/to/MSYS2]/ucrt64/bin`
    - The path to the Ninja file you downloaded in 2
7. Open the command prompt in the source files folder and run these two commands
    - `cmake --preset=default`:  loads build preset
    - `cmake --build build`:  makes the .exe

