#version 330 core

out vec4 FragColor;

in vec3 vertexNormal;
in vec3 fragPos;
in vec2 uvCoord;

uniform vec3 viewPos;
uniform vec3 lightDir;
uniform sampler2D mainTex;

void main()
{
	float ambiant = 0.6f;
	vec3 normal = normalize(vertexNormal);
	vec3 normalizedLightDir = normalize(-lightDir);
	float diffuse = max(dot(normal, normalizedLightDir), 0.0f);

	FragColor = texture(mainTex, uvCoord) * (diffuse + ambiant);
}