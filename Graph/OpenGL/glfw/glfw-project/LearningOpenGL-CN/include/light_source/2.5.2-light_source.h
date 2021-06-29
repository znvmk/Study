#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

//平行光
class ParallelLight
{
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction;
	glm::vec3 color;

public:
	ParallelLight(glm::vec3 _position , glm::vec3 _angles , glm::vec3 _direction = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		position = _position;
		angles = _angles;
		direction = _direction;
		color = _color;
	}
	~ParallelLight()
	{

	}

public:
	void UpdateDirection()
	{
		direction = glm::vec3(0.0f, 0.0f, 1.0f);
		//旋转方向顺序为zyx
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateY(direction, angles.y);
		direction = glm::rotateX(direction, angles.x);
		//把光源位置朝向转换为被照射物体朝向
		direction = -1.0f * direction;
	}


};

//点光源
class PointLight
{
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction;
	glm::vec3 color;
	//光源衰减:常数，一次，二次
	float constant, linear, quadratic;

public:
	PointLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _direction = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 _color = glm::vec3(5.0f, 5.0f, 5.0f))
	{
		position = _position;
		angles = _angles;
		direction = _direction;
		color = _color;

		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;
	}
	~PointLight()
	{

	}
};

//投影光
class SpotLight
{
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction;
	glm::vec3 color;
	//光源衰减:常数，一次，二次
	float constant, linear, quadratic;

	//角度
	float cosPhyInner;
	float cosPhyOutter;

public:
	SpotLight(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _direction = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 _color = glm::vec3(5.0f, 5.0f, 5.0f))
	{
		position = _position;
		angles = _angles;
		direction = _direction;
		color = _color;

		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;

		cosPhyInner = 0.9f;
		cosPhyOutter = 0.85;
	}
	~SpotLight()
	{

	}

public:
	void UpdateDirection()
	{
		direction = glm::vec3(0.0f, 0.0f, 1.0f);
		//旋转方向顺序为zyx
		direction = glm::rotateZ(direction, angles.z);
		direction = glm::rotateY(direction, angles.y);
		direction = glm::rotateX(direction, angles.x);
		//把光源位置朝向转换为被照射物体朝向
		direction = -1.0f * direction;
	}

};

#endif