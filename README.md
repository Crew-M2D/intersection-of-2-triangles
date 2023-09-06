# Intersection of polygons
HSE project

2nd course, 4th module

Subject: Web Technologies and Databases

### Task
The program should take the points of two polygons as input and find their intersection

### What we used
* Programming language: С++
* Build using cmake
* Libraries for graphics: GLFW, ImGui, OpenGl
* Unit-tests using gtest

### Results
* User-friendly graphical input
* Quick count of intersection points
* Visualization of the polygons, their intersections and a text window with details about the intersection
* Events are taken into account: there is no intersection, the polygon is not a polygon (the entered points are the same or form a line)
* Tests have been written for the possible number of points from 0 to 6 for triangles, as well as 28 tests for polygons
* Works in real-time, you don't need to restart the program to change the coordinates of polygons

### Example of work
![JAEQHQHjDx8](https://github.com/Crew-M2D/intersection-of-2-triangles/assets/87859313/913b4b0e-da27-4301-8fe4-569f4624ca51)


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
