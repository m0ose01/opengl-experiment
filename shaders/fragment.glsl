#version 330 core

in vec3 FragColor;
out vec4 FragColor2;

void main()
{
	FragColor2 = vec4(FragColor, 1.0);
}
