#ifndef STATE_H
#define STATE_H

#include <camera.h>
#include <input.h>

typedef struct Lighting {
	float ambientStrength;
	float diffuseStrength;
	float specularStrength;
	float shininess;
} Lighting;

typedef struct GameState {
	Camera camera;
	InputState input_state;
	Lighting lighting;
} GameState;

#endif
