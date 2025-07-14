#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


GLuint loadShader(const char *vertexPath, const char *fragmentPath)
{
	FILE *vertexFile = fopen(vertexPath, "rb");
	if (vertexFile == NULL)
	{
		fprintf(stderr, "Error loading vertex shader file: %s.\n", vertexPath);
		return 0;
	}
	fseek(vertexFile, 0, SEEK_END);
	long fileSize = ftell(vertexFile);
	fseek(vertexFile, 0, SEEK_SET);

	char *vertexShaderSource = calloc(1, fileSize + 1);
	if (fread(vertexShaderSource, fileSize, 1, vertexFile) != 1)
	{
		fprintf(stderr, "Error reading vertex shader file.\n");
		return 0;
	}


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		printf("Error compiling vertex shader: %s\n", log);
	}

	FILE *fragmentFile = fopen(fragmentPath, "rb");
	if (fragmentFile == NULL)
	{
		fprintf(stderr, "Error loading fragment shader file: %s.\n", fragmentPath);
		return 0;
	}
	fseek(fragmentFile, 0, SEEK_END);
	fileSize = ftell(fragmentFile);
	fseek(fragmentFile, 0, SEEK_SET);

	char *fragmentShaderSource = calloc(1, fileSize + 1);
	if (fread(fragmentShaderSource, fileSize, 1, fragmentFile) != 1)
	{
		fprintf(stderr, "Error reading fragment shader file.\n");
		return 0;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	memset(log, 0, sizeof(log));
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		fprintf(stderr, "Error compiling fragment shader: %s\n", log);
		return 0;
	}

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glLinkProgram(programID);

	memset(log, 0, sizeof(log));
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, log);
		fprintf(stderr, "Error linking shader program: %s\n", log);
		return 0;
	}

	return programID;
}

#endif
