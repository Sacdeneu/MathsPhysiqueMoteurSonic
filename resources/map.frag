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

	float uvX = mod(fragPos.x, 1);
	float uvY = mod(fragPos.y, 1);
	float uvZ = mod(fragPos.z, 1);
	float albedo = 0.4f;
	float threshold = 0.95f;
	if(uvX > threshold || uvY > threshold || uvZ > threshold)
		albedo = 0.6f;

	vec3 result = vec3(albedo, albedo, albedo) * (diffuse + ambiant);
	FragColor = vec4(result, 1.0);
}