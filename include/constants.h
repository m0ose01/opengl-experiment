#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

typedef enum DirectionFlag {
	FORWARDS = 32,
	BACKWARDS = 16,
	RIGHT = 8,
	LEFT = 4,
	UP = 2,
	DOWN = 1,
} DirectionFlag;

typedef uint8_t DirectionFlags;

#endif
