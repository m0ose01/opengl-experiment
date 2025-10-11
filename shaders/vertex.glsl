#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 lightPos;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float shininess;

out vec3 FragColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vec3 Normal = mat3(transpose(inverse(view * model))) * aNormal;
	vec3 Position = vec3(view * model * vec4(aPos, 1.0));

	vec3 ambient = ambientStrength * lightColour;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(vec3(view * vec4(lightPos, 1.0)) - Position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColour * diffuseStrength;

	vec3 viewDir = normalize(-Position);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = specularStrength * spec * lightColour;

	FragColor = (ambient + diffuse + specular) * objectColour;
}

