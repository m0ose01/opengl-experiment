#ifndef STATE_H
#define STATE_H

#include <camera.h>
#include <input.h>

typedef struct GameState {
	Camera camera;
	InputState input_state;
} GameState;

#endif
