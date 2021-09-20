#version 330 core

out vec4 FragColor;

in vec3 vertexNormal;
in vec3 fragPos;

uniform vec3 viewPos;
uniform vec3 lightDir;

void main()
{
	float ambiant = 0.3f;
	vec3 normal = normalize(vertexNormal);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	// specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);


	vec3 result = vec3(0.168f, 0.384f, 0.96f) * (diffuse + ambiant + spec);
	FragColor = vec4(result, 1.0);
}