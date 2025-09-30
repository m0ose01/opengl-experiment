cmake_minimum_required(VERSION 3.28)
project(my_graphics_project)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(cglm)

add_executable(game src/main.c)

add_library(stb_image src/stb_image.c)
add_library(texture src/texture.c)
add_library(shader src/shader.c)
add_library(camera src/camera.c)
add_library(input src/input.c)

target_include_directories(game PRIVATE include)
target_include_directories(stb_image PUBLIC stb)
target_include_directories(shader PRIVATE include)
target_include_directories(texture PRIVATE include)
target_include_directories(camera PRIVATE include)
target_include_directories(input PRIVATE include cglm/include) # don't need to link to cglm, only needed because of camera.h.

target_link_libraries(game glfw glad stb_image cglm texture shader camera input)
target_link_libraries(camera glfw cglm)
target_link_libraries(input glfw)
target_link_libraries(shader glad stb_image)
target_link_libraries(texture glad stb_image)
