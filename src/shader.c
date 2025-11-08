#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include <shader.h>
#include <cglm/cglm.h>

GLuint loadShader(const char *vertex_path, const char *fragment_path)
{
	const char *shader_paths[] = {vertex_path, fragment_path};
	const GLuint shader_types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	GLuint shaders[2] = { 0 };

	GLuint shader_program = glCreateProgram();

	for (int current_shader = 0; current_shader < 2; current_shader++)
	{
		FILE *current_shader_file = fopen(shader_paths[current_shader], "rb");
		if (current_shader_file == NULL)
		{
			fprintf(stderr, "Error opening shader file: '%s'\n", shader_paths[current_shader]);
			return 0;
		}

		// Get shader source file size
		fseek(current_shader_file, 0, SEEK_END);
		long file_size = ftell(current_shader_file);
		fseek(current_shader_file, 0, SEEK_SET);

		// using calloc and allocating an extra byte will automatically null-terminate the string.
		char *shader_source = calloc(1, file_size + 1);
		if (fread(shader_source, file_size, 1, current_shader_file) != 1)
		{
			fprintf(stderr, "Error reading shader file '%s'\n", shader_paths[current_shader]);
			return 0;
		}
		fclose(current_shader_file);

		shaders[current_shader] = glCreateShader(shader_types[current_shader]);
		glShaderSource(shaders[current_shader], 1, &shader_source, NULL);
		glCompileShader(shaders[current_shader]);
		free(shader_source);

		int compilation_successful = 0;
		char log[512] = { 0 };
		glGetShaderiv(shaders[current_shader], GL_COMPILE_STATUS, &compilation_successful);
		if (!compilation_successful)
		{
			glGetShaderInfoLog(shaders[current_shader], 512, NULL, log);
			fprintf(stderr, "Error compiling shader file '%s'. See log for more info:\n '%s'\n", shader_paths[current_shader], log);
			return 0;
		}

		glAttachShader(shader_program, shaders[current_shader]);
	}

	glLinkProgram(shader_program);

	int linking_successful = 0;
	char log[512] = { 0 };
	glGetProgramiv(shader_program, GL_LINK_STATUS, &linking_successful);
	if (!linking_successful)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, log);
		fprintf(stderr, "Error linking shader. See log for more info:\n, '%s'\n", log);
		return 0;
	}

	return shader_program;
}

void initPointLight(Light *light, vec3 position, vec3 colour, float ambient, float diffuse, float specular, float constant, float linear, float quadratic)
{
	glm_vec3_copy(position, light->position);
	glm_vec3_copy(colour, light->colour);

	glm_vec3_scale(colour, ambient, light->ambient);
	glm_vec3_scale(colour, diffuse, light->diffuse);
	glm_vec3_scale(colour, specular, light->specular);

	light->constant = constant;
	light->linear = linear;
	light->quadratic = quadratic;
}

