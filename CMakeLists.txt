cmake_minimum_required(VERSION 3.28)
project(my_graphics_project)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(cglm)

add_executable(hello src/main.c)

add_library(stb_image src/stb_image.c)
add_library(texture src/texture.c)
add_library(shader src/shader.c)
add_library(camera src/camera.c)

target_include_directories(hello PRIVATE include)
target_include_directories(stb_image PUBLIC stb)
target_include_directories(shader PRIVATE include)
target_include_directories(texture PRIVATE include)
target_include_directories(camera PRIVATE include)

target_link_libraries(hello glfw glad stb_image texture shader camera)
target_link_libraries(hello cglm)
target_link_libraries(camera glfw cglm)
target_link_libraries(shader glad stb_image)
target_link_libraries(texture glad stb_image)
