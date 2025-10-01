#include <camera.h>

void initialise_camera(Camera *camera)
{
	camera->pitch = 0.0f;
	camera->yaw = -90.0f;

	camera->position[0] = 0.0f;
	camera->position[1] = 0.0f;
	camera->position[2] = 3.0f;

	camera->front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
	camera->front[1] = sin(glm_rad(camera->pitch));
	camera->front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));

	camera->fov = 45.0f;
}

void rotate_camera(Camera *camera)
{
	camera->front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
	camera->front[1] = sin(glm_rad(camera->pitch));
	camera->front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
	glm_normalize(camera->front);
}

void move_camera(Camera *camera, DirectionFlags direction_flags, float delta_time)
{
	const float translation_speed = 10.0f;
	vec3 worldUp = {0.0f, 1.0f, 0.0f};

	vec3 cameraForward = {0, 0, 0};
	glm_vec3_scale(camera->front, translation_speed * delta_time, cameraForward);

	vec3 cameraUp = {0, 0, 0};
	glm_vec3_scale(worldUp, translation_speed * delta_time, cameraUp);

	vec3 cameraRight = {0, 0, 0};
	glm_vec3_cross(cameraForward, worldUp, cameraRight);
	glm_vec3_normalize(cameraRight);
	glm_vec3_scale(cameraRight, translation_speed * delta_time, cameraRight);

	if (direction_flags & FORWARDS)
	{
		glm_vec3_add(camera->position, cameraForward, camera->position);
	}
	if (direction_flags & BACKWARDS)
	{
		glm_vec3_sub(camera->position, cameraForward, camera->position);
	}
	if (direction_flags & RIGHT)
	{
		glm_vec3_add(camera->position, cameraRight, camera->position);
	}
	if (direction_flags & LEFT)
	{
		glm_vec3_sub(camera->position, cameraRight, camera->position);
	}
	if (direction_flags & UP)
	{
		glm_vec3_add(camera->position, cameraUp, camera->position);
	}
	if (direction_flags & DOWN)
	{
		glm_vec3_sub(camera->position, cameraUp, camera->position);
	}

	camera->position[1] = 0.0f;
}
