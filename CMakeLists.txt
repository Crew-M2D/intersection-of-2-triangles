set(CMAKE_MAKE_PROGRAM make)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.15)
project(intersection_of_2_triangles CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendors/glad)
add_subdirectory(vendors/glfw)
add_subdirectory(vendors/imgui)

add_subdirectory(src/Common)
add_subdirectory(src/Graphics)
add_subdirectory(src/Input)
add_subdirectory(src/Math)
add_subdirectory(src/Entrypoint)

# add_subdirectory(tests)
