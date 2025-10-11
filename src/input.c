#include <GLFW/glfw3.h>

#include <input.h>
#include <state.h>

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
	if (key ==  GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		*direction_flags = *direction_flags | LEFT;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		*direction_flags = *direction_flags | RIGHT;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
	{
		*direction_flags = *direction_flags | UP;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
	{
		*direction_flags = *direction_flags | DOWN;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		*direction_flags = *direction_flags | FORWARDS;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		*direction_flags = *direction_flags | BACKWARDS;
	}

	// On key release, zero the relevant bit using & ~ of the relevant bitflag.
	if (key ==  GLFW_KEY_LEFT && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~LEFT;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~RIGHT;
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~(DOWN | UP);
	}
	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~FORWARDS;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
	{
		*direction_flags = *direction_flags & ~BACKWARDS;
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
	{
		game->lighting.ambientStrength += 0.1;
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
	{
		game->lighting.ambientStrength -= 0.1;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
	{
		game->lighting.diffuseStrength += 0.1;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
	{
		game->lighting.diffuseStrength -= 0.1;
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
	{
		game->lighting.specularStrength += 0.1;
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
	{
		game->lighting.specularStrength -= 0.1;
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS && !(mods & GLFW_MOD_SHIFT))
	{
		game->lighting.shininess += 1.0;
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS && (mods & GLFW_MOD_SHIFT))
	{
		game->lighting.shininess -= 1.0;
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

