#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <constants.h>

typedef struct MouseState {
	float last_x;
	float last_y;
	bool first_mouse;
} MouseState;

typedef struct InputState {
	MouseState mouse_state;
	DirectionFlags direction;
} InputState;

void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void initialise_input(InputState *input_state);

#endif
