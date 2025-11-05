#include "cglm/vec3.h"
#include <stdbool.h>
#include <stdio.h>

#include <game.h>
#include <shader.h>
#include <texture.h>
#include <camera.h>
#include <state.h>
#include <input.h>

#include <cglm/cglm.h>
#include <cglm/affine.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#define WINDOW_HEIGHT 600.0f
#define WINDOW_WIDTH 800.0f

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
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

	int framebuffer_width, framebuffer_height;
	glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);

	glViewport(0, 0, framebuffer_width, framebuffer_height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	GLuint shaderProgram = loadShader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
	if (shaderProgram == 0)
	{
		return 1;
	}
	GLuint shaderProgram2 = loadShader("./shaders/vertex.glsl", "./shaders/fragment2.glsl");
	if (shaderProgram2 == 0)
	{
		return 1;
	}

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	float cubePosition[] = {
		0.0f, 0.0f, 0.0f,
	};
	float lightPosition[] = {
		1.2f, 1.0f, 2.0f
	};

	Light light;
	glm_vec3_copy(lightPosition, light.position);

	vec3 lightColour = {1.0f, 1.0f, 1.0f};
	float ambientStrength = 0.2f;
	float diffuseStrength = 0.5f;
	float specularStrength = 1.0f;
	glm_vec3_scale(lightColour, ambientStrength, light.ambient);
	glm_vec3_scale(lightColour, diffuseStrength, light.diffuse);
	glm_vec3_scale(lightColour, specularStrength, light.specular);

	Material cubeMaterial =  {
		.diffuseMap = loadTexture("./textures/container2.png", GL_REPEAT, GL_REPEAT),
		.specularMap = loadTexture("./textures/container2_specular.png", GL_REPEAT, GL_REPEAT),
		.shininess = 32.0f,
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);


	int modelLocation = glGetUniformLocation(shaderProgram, "model");
	int viewLocation = glGetUniformLocation(shaderProgram, "view");
	int projectionLocation = glGetUniformLocation(shaderProgram, "projection");

	int viewLocationLocation = glGetUniformLocation(shaderProgram, "viewPos");

	MaterialLocations materialLocations = {0};
	LightLocations lightLocations = {0};

	materialLocations.diffuse = glGetUniformLocation(shaderProgram, "material.diffuse");
	materialLocations.specular = glGetUniformLocation(shaderProgram, "material.specular");
	materialLocations.shininess = glGetUniformLocation(shaderProgram, "material.shininess");

	lightLocations.position = glGetUniformLocation(shaderProgram, "light.position");
	lightLocations.ambient = glGetUniformLocation(shaderProgram, "light.ambient");
	lightLocations.diffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightLocations.specular = glGetUniformLocation(shaderProgram, "light.specular");

	int lightModelLocation = glGetUniformLocation(shaderProgram2, "model");
	int lightViewLocation = glGetUniformLocation(shaderProgram2, "view");
	int lightProjectionLocation = glGetUniformLocation(shaderProgram2, "projection");
	int lightSourceColorLocation = glGetUniformLocation(shaderProgram2, "lightColour");

	GameState game;
	initialise_game(&game);

	glfwSetWindowUserPointer(window, &game);

	vec3 cameraTarget;
	glm_vec3_add(game.camera.position, game.camera.front, cameraTarget);

	vec3 worldUp = {0.0f, 1.0f, 0.0f};

	mat4 view;
	glm_lookat(game.camera.position, cameraTarget, worldUp, view);

	const float translationSpeed = 10.0f;

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

		double time = glfwGetTime();

		glm_vec3_scale(lightColour, ambientStrength, light.ambient);
		glm_vec3_scale(lightColour, diffuseStrength, light.diffuse);
		// glm_vec3_scale(lightColour, specularStrength, light.specular);

		move_camera(&(game.camera), game.input_state.direction, deltaTime);

		glBindVertexArray(VAO);

		glm_vec3_add(game.camera.position, game.camera.front, cameraTarget);
		glm_lookat(game.camera.position, cameraTarget, worldUp, view);

		mat4 projection = GLM_MAT4_IDENTITY_INIT;
		float aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
		glm_perspective(glm_rad(game.camera.fov), aspectRatio, 0.1f, 100.0f, projection);

		mat4 model = GLM_MAT4_IDENTITY_INIT;
		glm_translate(model, cubePosition);

		glUniform3fv(viewLocationLocation, 1, game.camera.position);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeMaterial.diffuseMap);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, cubeMaterial.specularMap);

		glUniform1i(materialLocations.diffuse, 0);
		glUniform1i(materialLocations.specular, 1);
		glUniform1f(materialLocations.shininess, cubeMaterial.shininess);

		glUniform3fv(lightLocations.position, 1, light.position);
		glUniform3fv(lightLocations.ambient, 1, light.ambient);
		glUniform3fv(lightLocations.diffuse, 1, light.diffuse);
		glUniform3fv(lightLocations.specular, 1, light.specular);

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, (float *)model);
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float *)view);
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, (float *)projection);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUseProgram(shaderProgram2);
		glUniform3fv(lightSourceColorLocation, 1, lightColour);

		glBindVertexArray(lightVAO);
		mat4 lightModel = GLM_MAT4_IDENTITY_INIT;
		glm_translate(lightModel, light.position);
		glm_scale_uni(lightModel, 0.2f);

		glUniformMatrix4fv(lightModelLocation, 1, GL_FALSE, (float *)lightModel);
		glUniformMatrix4fv(lightViewLocation, 1, GL_FALSE, (float *)view);
		glUniformMatrix4fv(lightProjectionLocation, 1, GL_FALSE, (float *)projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

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

void initialise_game(GameState *game)
{
	initialise_camera(&(*game).camera);
	initialise_input(&(*game).input_state);
}
