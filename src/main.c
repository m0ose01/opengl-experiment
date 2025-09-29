#include "cglm/vec3.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include <hello.h>
#include <shader.h>
#include <texture.h>

#include <cglm/cglm.h>
#include <cglm/affine.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

float lastX = 400, lastY = 300;
float cameraPitch_deg = 0.0f, cameraYaw_deg = -90.0f;
float fov = 45.0f;
bool firstMouse = true;

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD.\n");
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	GLuint shaderProgram = loadShader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
	if (shaderProgram == 0)
	{
		return 1;
	}

	char *texture1Path = "textures/container.jpg";
	char *texture2Path = "textures/awesomeface.png";
	GLuint texture1 = loadTexture(texture1Path, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);
	GLuint texture2 = loadTexture(texture2Path, GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vec3 cubePositions[] = {
		{ 0.0f,  0.0f,  0.0f},
		{ 2.0f,  5.0f, -15.0f},
		{-1.5f, -2.2f, -2.5f},
		{-3.8f, -2.0f, -12.3f},
		{ 2.4f, -0.4f, -3.5f},
		{-1.7f,  3.0f, -7.5f},
		{ 1.3f, -2.0f, -2.5f},
		{ 1.5f,  2.0f, -2.5f},
		{ 1.5f,  0.2f, -1.5f},
		{-1.3f,  1.0f, -1.5f},
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	int modelLocation = glGetUniformLocation(shaderProgram, "model");
	int viewLocation = glGetUniformLocation(shaderProgram, "view");
	int projectionLocation = glGetUniformLocation(shaderProgram, "projection");

	vec3 cameraPosition = {0.0f, 0.0f, 3.0f};
	vec3 cameraFront = {
		cos(glm_rad(cameraYaw_deg)) * cos(glm_rad(cameraPitch_deg)),
		sin(glm_rad(cameraPitch_deg)),
		sin(glm_rad(cameraYaw_deg)) * cos(glm_rad(cameraPitch_deg)),
	};
	vec3 cameraTarget;
	glm_vec3_add(cameraPosition, cameraFront, cameraTarget);

	vec3 worldUp = {0.0f, 1.0f, 0.0f};

	mat4 view;
	glm_lookat(cameraPosition, cameraTarget, worldUp, view);

	vec3 viewTranslation = {0.0f, 0.0f, -3.0f};
	const float translationSpeed = 10.0f;
	const float radius = 10.0f;

	glEnable(GL_DEPTH_TEST);

	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	while(!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);

		double time = glfwGetTime();

		cameraFront[0] = cos(glm_rad(cameraYaw_deg)) * cos(glm_rad(cameraPitch_deg));
		cameraFront[1] = sin(glm_rad(cameraPitch_deg));
		cameraFront[2] = sin(glm_rad(cameraYaw_deg)) * cos(glm_rad(cameraPitch_deg));
		glm_normalize(cameraFront);

		vec3 cameraForward = {0, 0, 0};
		glm_vec3_scale(cameraFront, translationSpeed * deltaTime, cameraForward);

		vec3 cameraUp = {0, 0, 0};
		glm_vec3_scale(worldUp, translationSpeed * deltaTime, cameraUp);

		vec3 cameraRight = {0, 0, 0};
		glm_vec3_cross(cameraForward, worldUp, cameraRight);
		glm_vec3_normalize(cameraRight);
		glm_vec3_scale(cameraRight, translationSpeed * deltaTime, cameraRight);

		// TODO: Figure out how to do this in a cleaner/more scaleable way
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			glm_vec3_sub(cameraPosition, cameraRight, cameraPosition);
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			glm_vec3_add(cameraPosition, cameraRight, cameraPosition);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS)
		{
			glm_vec3_add(cameraPosition, cameraUp, cameraPosition);
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			glm_vec3_sub(cameraPosition, cameraUp, cameraPosition);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			glm_vec3_add(cameraPosition, cameraForward, cameraPosition);
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			glm_vec3_sub(cameraPosition, cameraForward, cameraPosition);
		}

		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glm_vec3_add(cameraPosition, cameraFront, cameraTarget);
		glm_lookat(cameraPosition, cameraTarget, worldUp, view);

		mat4 projection = GLM_MAT4_IDENTITY_INIT;
		float aspectRatio = 800.0f / 600.0f;
		glm_perspective(glm_rad(fov), aspectRatio, 0.1f, 100.0f, projection);

		for (int currentCube = 0; currentCube < 10; currentCube++)
		{
			mat4 model = GLM_MAT4_IDENTITY_INIT;
			vec3 modelRotationAxis = {0.5f, 1.0f, 0.0f};
			glm_translate(model, cubePositions[currentCube]);
			float rotationSpeed = 50.0f;
			float rotationOffset = 20.0f;
			float angle = glm_rad(
				(currentCube % 3 == 0) * time * rotationSpeed
				+ rotationOffset * currentCube
			);
			glm_rotate(model, angle, modelRotationAxis);

			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, (float *)model);
			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float *)view);
			glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, (float *)projection);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = (ypos - lastY) * -1;
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;

	cameraYaw_deg += xoffset * sensitivity;
	cameraPitch_deg += yoffset * sensitivity;

	if (cameraPitch_deg > 89.0f)
	{
		cameraPitch_deg = 89.0f;
	}
	if (cameraPitch_deg < -89.0f)
	{
		cameraPitch_deg = -89.0f;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
	{
		fov = 1.0f;
	}
    if (fov > 45.0f)
	{
		fov = 45.0f;
	}
}
