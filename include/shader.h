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
	GLuint direction;

	GLuint ambient;
	GLuint diffuse;
	GLuint specular;

	GLuint constant;
	GLuint linear;
	GLuint quadratic;
	GLuint cutoff_costheta;
} LightLocations;

typedef struct Light {
	vec3 position;
	vec3 direction;
	vec3 colour;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
	float cutoff_costheta;
} Light;

GLuint loadShader(const char *vertexPath, const char *fragmentPath);
void initPointLight(Light *light, vec3 position, vec3 colour, float ambient, float diffuse, float specular, float constant, float linear, float quadratic);

#endif
