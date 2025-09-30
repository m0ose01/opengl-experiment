#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <constants.h>

typedef struct Camera {
	vec3 position;
	vec3 front;
	float pitch;
	float yaw;
	float fov;
} Camera;

void initialise_camera(Camera *camera);
void rotate_camera(Camera *camera);
void move_camera(Camera *camera, DirectionFlags direction_flags, float delta_time);

#endif
