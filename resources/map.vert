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

	float absNX = abs(vertexNormal.x);
	float absNY = abs(vertexNormal.y);
	float absNZ = abs(vertexNormal.z);
	if(absNX > absNY && absNX > absNY) // projection sur X
		uvCoord = vec2(fragPos.z, fragPos.y) * 0.5;
	else if(absNY > absNX && absNY > absNZ) // projection sur Y
		uvCoord = vec2(fragPos.x, fragPos.z) * 0.5;
	else // projection sur Z
		uvCoord = vec2(fragPos.x, fragPos.y) * 0.5;

	gl_Position = cameraMatrix * vec4(fragPos, 1.0);
	
}