cmake_minimum_required(VERSION 3.28)
project(my_graphics_project)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hello src/main.c)

add_subdirectory(glfw)
target_link_libraries(hello glfw)
