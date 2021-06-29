#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//out vec3 ourColor;
//out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
	//反序相乘
	//gl_Position = transform * projMat * viewMat * modelMat * vec4(aPos, 1.0);
	gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);
	//ourColor = aColor;
	//TexCoord = vec2(aTexCoord.x, 1.0-aTexCoord.y);
	FragPos=(modelMat * vec4(aPos.xyz,1.0)).xyz;
	Normal = mat3(modelMat) * aNormal;
}