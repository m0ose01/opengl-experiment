#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <constants.h>

typedef struct Camera {
	vec3 position;
	vec3 front;
	float _pitch;
	float _yaw;
	float fov;
} Camera;

void initialise_camera(Camera *camera);
void rotate_camera(Camera *camera, float delta_pitch, float delta_yaw);
void translate_camera(Camera *camera, DirectionFlags direction_flags, float translation_distance);

#endif
