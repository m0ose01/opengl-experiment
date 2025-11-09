#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 viewPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutoff_costheta;
};

uniform Material material;
uniform Light light;

void main()
{
	vec3 light_vector = light.position - FragPos;
	float costheta = dot( normalize(light_vector),
		normalize(-light.direction)
	);

	// check if light is directional
	vec3 result;

	// ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	if (costheta > light.cutoff_costheta && length(light.direction) > 0)
	{
		// float light_distance = length(light_vector);
		// float attenuation = 1.0 / (light.constant + light.linear * light_distance + light.quadratic * pow(light_distance, 2));

		// needed for diffuse/specular lighting
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light_vector);

		// diffuse
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * light.diffuse * vec3(texture(material.diffuse, TexCoords));

		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = spec * light.specular * vec3(texture(material.specular, TexCoords));

		result = ambient + diffuse + specular;
	}
	else
	{
		result = ambient;
	}

	FragColor = vec4(result, 1.0);
}
