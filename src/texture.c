#ifndef SHADER_H
#define SHADER_H

#include <texture.h>

#include <glad/glad.h>
#include <stb_image.h>

#include <stdbool.h>

GLuint loadTexture(char *texturePath, int wrapS, int wrapT)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data == NULL)
	{
		fprintf(stderr, "Error loading image. %s\n", texturePath);
		return 0;
	}

	int internalFormat = nrChannels > 3 ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	return texture;
}

#endif
