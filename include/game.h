#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <camera.h>
#include <input.h>
#include <state.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void initialise_game(GameState *game);

#endif
