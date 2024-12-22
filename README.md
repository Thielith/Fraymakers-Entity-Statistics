# Fraymakers-Entity-Statistics
 Prints out statistics related to an Fraymakers Custom Content .entity file.

## Usage
Define the .entity file to be used with `(--file or -f) [path-to-file]`

If you want to output to a file, use flag `(--output or -o) [path/to/save/output.txt]`

## Usage (Devs)
### Linux
1. Download source files.
2. Run the makefile.

### Windows
ok so i couldn't get the cross-platform compiler working on my system because it can't find the `jsoncpp` libraries (even though they're installed).
this is probably because my makefile isn't linking stuff correctly but i've spent too long trying to fix it.
HOWEVER, i got a work around:
1. Install [VS Code](https://code.visualstudio.com/) and install the C/C++ extension.  I'm abusing the fact that it can generate .exe files to make the .exe file.  Yes, this is jank.
2. Download `jsoncpp` from the [source](https://github.com/open-source-parsers/jsoncpp).
3. Extract the contents into a new folder named `external`.  File structure should look like: `external/jsoncpp-master/[a bunch of files]`.
4. In `jsoncpp-master/src/lib_json`, do the following to these files:
	- `json_tool.h`:
		- `<json/config.h>` to `"../../include/json/config.h"`
	- `json_writer.cpp`:
		- `<json/writer.h>` to `"../../include/json/writer.h"`
	- `json_value.cpp` and `json_reader.cpp`:
		- `<json/assertions.h>` to `"../../include/json/assertions.h`
		- `<json/value.h>` to `"../../include/json/value.h`
		- `<json/writer.h>` to `"../../include/json/writer.h`
5. In `program.h`, uncomment the `#include`s under `Windows` and comment out the `#include` under `Linux`.
6. Click the play/run button (>) to run the `program.cpp` file and choose the `C/C++: g++` debug configuration.
	- It'll generate an .exe file but you can't run it externally due to missing .dlls.
7. In `.vscode/tasks.json`, add `-static` to the end of the `args` array.
8. Run `program.cpp` again and the resulting .exe file should work now.
