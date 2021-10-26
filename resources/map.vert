#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 vertexNormal;
out vec3 fragPos;
out vec2 uvCoord;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
	fragPos = vec3(model * vec4(aPos, 1.0f));
	vertexNormal = aNormal;
	uvCoord = vec2(fragPos.x, fragPos.y + fragPos.z) * 0.5;

	gl_Position = cameraMatrix * vec4(fragPos, 1.0);
	
}