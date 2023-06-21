# Intersection of 2 triangles
Hse project

### How to setup and run
1. Install cmake
Windows:
```bash
winget install -e --id Kitware.CMake
```
2. Install clang
```bash
winget install -e --id LLVM.LLVM
```
3. Make sure cmake and llvm in PATH
4. Restart PC
5. Ensure cmake and clang are installed properly:
```bash
clang++ --version
```
```bash
cmake --version
```
```bash
make --version
```
if there are errors go back to point 3

6. Configure project:
```bash
cmake -S . -B build -G"MinGW Makefiles" -D"CMAKE_MAKE_PROGRAM:PATH=C:\Program Files (x86)\GnuWin32\bin\make"
```
Specify last flag with your make path. 
7. Build:
```bash
cmake --build build
```

### Usage:
To run program:
```bash
./build/src/Entrypoint/Entrypoint
```

To run tests:
```bash
cd build/tests
ctest
```

### Contributing:
*Codestyle:*
Type and class names: `UpperCamelCase`
Variables, methods and functions: 'lower_snake_case'

*Developing setup:*
Highly recommended using vscode/fleet with clangd.
Also locate your project in C:\ if your username in cyrillic (!)

*formatting*
Using clang-format for formatting code (make sure it is not affecting on your `#include` order)
