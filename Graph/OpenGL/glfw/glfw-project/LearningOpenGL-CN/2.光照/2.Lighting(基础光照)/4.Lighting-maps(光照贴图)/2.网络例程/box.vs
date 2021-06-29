#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textCoord;
out vec3 color;
out vec3 normal_frag;
out vec3 fragPos;
out vec2 atextcoord;
uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;
void main() {
	gl_Position = projection * view * model * vec4(aPos,1.0);
	fragPos = vec3(model * vec4(aPos,1.0));
	normal_frag = mat3(transpose(inverse(model))) * normal;
	atextcoord = textCoord;
}