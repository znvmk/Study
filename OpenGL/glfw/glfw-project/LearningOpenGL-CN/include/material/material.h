#ifndef MATERIAL_H
#define MATERIAL_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader/shader.h>

class Material
{
public:
	Shader* shader;
	//漫反射贴图
	GLuint diffuse;
	//镜面光贴图
	GLuint specular;
	//发射光贴图
	GLuint refTex;
	float shininess;

public:
/*
	Material(Shader* _shader, GLuint _diffuse, GLint _specular, GLuint _refTex, float _shininess)
	{
		shader = _shader;
		diffuse = _diffuse;
		specular = _specular;
		refTex = _refTex;
		shininess = _shininess;
	}
	*/
	//*
	Material(Shader* _shader,  GLuint _diffuse, GLuint _refTex, float _shininess)
	{
		shader = _shader;
		//ambient = _ambient;
		diffuse = _diffuse;
		//specular = _specular;
		refTex = _refTex;
		shininess = _shininess;
	}
	//*/
	~Material()
	{

	}

public:

};

#endif