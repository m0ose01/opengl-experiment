#version 330 core

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 lightPos;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColour;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColour;

	vec3 result = (ambient + diffuse) * objectColour;
	FragColor = vec4(result, 1.0);
}
