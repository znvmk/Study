#include "mycame.h"

mycame::mycame(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Positon = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}
mycame::mycame(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Positon = position;
	WorldUp = worldup;
	Forward.x = glm::cos(pitch) * glm::sin(yaw);
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Forward, Right));
}
mycame::~mycame()
{

}
glm::mat4 mycame::GetViewMatrix()
{
	return glm::lookAt(Positon, Positon + Forward, WorldUp);
}