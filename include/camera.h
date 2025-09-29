#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

typedef struct Camera {
	vec3 position;
	vec3 front;
	float pitch;
	float yaw;
	float fov;
} Camera;

typedef enum DirectionFlag {
	FORWARDS = 32,
	BACKWARDS = 16,
	RIGHT = 8,
	LEFT = 4,
	UP = 2,
	DOWN = 1,
} DirectionFlag;

typedef uint8_t DirectionFlags;

typedef struct Mouse {
	float lastX;
	float lastY;
} Mouse;

void initialise_camera(Camera *camera);
void rotate_camera(Camera *camera);
void move_camera(Camera *camera, DirectionFlags direction_flags, float delta_time);

#endif
