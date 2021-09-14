#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 pos;
uniform vec3 lightPos;
void main()
{
	float ambiant = 0.3f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - pos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);
	FragColor = vec4(0.9f, 0.8f, 0.7f, 1.0f) * diffuse + ambiant;
}