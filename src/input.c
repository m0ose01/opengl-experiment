#include <GLFW/glfw3.h>

#include <input.h>
#include <state.h>

void initialise_input(InputState *input_state)
{
	input_state->mouse_state.last_x = 400;
	input_state->mouse_state.last_y = 300;
	input_state->mouse_state.first_mouse =- true;
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	GameState *game = glfwGetWindowUserPointer(window);
	Camera *camera = &(game->camera);
	MouseState *mouse_state = &(game->input_state.mouse_state);

	if (mouse_state->first_mouse)
	{
		mouse_state->last_x = xpos;
		mouse_state->last_y = ypos;
		mouse_state->first_mouse = false;
	}

	float xoffset = xpos - mouse_state->last_x;
	float yoffset = (ypos - mouse_state->last_y) * -1;
	mouse_state->last_x = xpos;
	mouse_state->last_y = ypos;

	const float sensitivity = 0.1f;

	camera->yaw += xoffset * sensitivity;
	camera->pitch += yoffset * sensitivity;

	if (camera->pitch > 89.0f)
	{
		camera->pitch = 89.0f;
	}
	if (camera->pitch < -89.0f)
	{
		camera->pitch = -89.0f;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	GameState *game = glfwGetWindowUserPointer(window);
	Camera *camera = &(game->camera);

	camera->fov -= (float)yoffset;
	if (camera->fov < 1.0f)
	{
		camera->fov = 1.0f;
	}
	if (camera->fov > 45.0f)
	{
		camera->fov = 45.0f;
	}
}

