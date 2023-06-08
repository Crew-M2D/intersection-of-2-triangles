cmake_minimum_required(VERSION 3.15)
project(intersection_of_2_triangles CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src/Common)
add_subdirectory(src/Graphics)
add_subdirectory(src/Input)
add_subdirectory(src/Math)
add_subdirectory(src/Entrypoint)

add_subdirectory(tests)
