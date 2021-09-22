#version 330 core

out vec4 FragColor;

in vec3 vertexNormal;
in vec3 fragPos;

uniform vec3 viewPos;
uniform vec3 lightDir;

void main()
{
	float ambiant = 0.6f;
	vec3 normal = normalize(vertexNormal);
	vec3 normalizedLightDir = normalize(-lightDir);
	float diffuse = max(dot(normal, normalizedLightDir), 0.0f);

	// specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-normalizedLightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);

	vec3 debug = vec3(0.5, 0.5, 0.5) + normal * 0.5;

	vec3 result = vec3(0.168f, 0.384f, 0.96f) * (diffuse + ambiant + spec);
	FragColor = vec4(result, 1.0);
}