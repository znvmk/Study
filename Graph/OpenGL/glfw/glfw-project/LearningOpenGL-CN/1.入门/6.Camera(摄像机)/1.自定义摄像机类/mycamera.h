#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class mycame
{
public:
	mycame(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	mycame(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	~mycame();

public:
	glm::vec3 Positon, Forward, Right, Up, WorldUp;
public:
	glm::mat4 GetViewMatrix();
};

