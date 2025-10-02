#version 330 core

out vec4 FragColor;

uniform vec3 objectColour;
uniform vec3 lightColour;

void main()
{
	// lightColour = vec3(1.0f, 1.0f, 1.0f);
	// objectColour = vec3(1.0f, 0.5f, 0.31f);
	FragColor = vec4(lightColour * objectColour, 1.0);
}
