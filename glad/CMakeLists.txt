cmake_minimum_required(VERSION 3.28)
project(Glad)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(glad "src/glad.c")
target_include_directories(glad PUBLIC include)
