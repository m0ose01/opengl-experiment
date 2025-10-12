#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

typedef struct MaterialLocations {
	GLuint ambient;
	GLuint diffuse;
	GLuint specular;
	GLuint shininess;
} MaterialLocations;

typedef struct LightLocations {
	GLuint position;
	GLuint ambient;
	GLuint diffuse;
	GLuint specular;
} LightLocations;

GLuint loadShader(const char *vertexPath, const char *fragmentPath);

#endif
