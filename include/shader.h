#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <cglm/cglm.h>

typedef struct MaterialLocations {
	GLuint ambient;
	GLuint diffuse;
	GLuint specular;
	GLuint shininess;
} MaterialLocations;

typedef struct Material {
	GLuint diffuseMap;
	GLuint specularMap;
	float shininess;
} Material;

typedef struct LightLocations {
	GLuint position;
	GLuint ambient;
	GLuint diffuse;
	GLuint specular;
} LightLocations;

typedef struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
} Light;

GLuint loadShader(const char *vertexPath, const char *fragmentPath);

#endif
