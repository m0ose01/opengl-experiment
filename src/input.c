#include <GLFW/glfw3.h>

#include <input.h>
#include <state.h>

#define LEFT_KEY GLFW_KEY_A
#define RIGHT_KEY GLFW_KEY_D
#define FORWARD_KEY GLFW_KEY_W
#define BACK_KEY GLFW_KEY_S
#define VERTICAL_KEY GLFW_KEY_SPACE
#define DOWN_MOD GLFW_MOD_SHIFT

void initialise_input(InputState *input_state)
{
	input_state->mouse_state.last_x = 400;
	input_state->mouse_state.last_y = 300;
	input_state->mouse_state.first_mouse =- true;

	input_state->direction = 0;
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	GameState *game = glfwGetWindowUserPointer(window);
	DirectionFlags *direction_flags = &(game->input_state.direction);

	// Use | to set the relevant bitfield to 1.
	if (key == LEFT_KEY && action == GLFW_PRESS)
	{
		*direction_flags = *direction_flags | LEFT;
	}
	if (key == RIGHT_KEY && action == GLFW_PRESS)
	{
		*direction_flags = *direction_flags | RIGHT;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !(mods & DOWN_MOD))
	{
		*direction_flags = *direction_flags | UP;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && (mods & DOWN_MOD))
	{
		*direction_flags = *direction_flags | DOWN;
	}
	if (key == FORWARD_KEY && action == GLFW_PRESS)
	{
		*direction_flags = *direction_flags | FORWARDS;
	}
	if (key == BACK_KEY && action == GLFW_PRESS)
	{
		*direction_flags = *direction_flags | BACKWARDS;
	}

	// On key release, zero the relevant bit using & ~ of the relevant bitflag.
	if (key ==  LEFT_KEY && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~LEFT;
	}
	if (key == RIGHT_KEY && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~RIGHT;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~(DOWN | UP);
	}
	if (key == FORWARD_KEY && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~FORWARDS;
	}
	if (key == BACK_KEY && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~BACKWARDS;
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

	const float delta_yaw = xoffset * sensitivity;
	const float delta_pitch = yoffset * sensitivity;
	rotate_camera(camera, delta_yaw, delta_pitch);

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

