#pragma once
#include<stdafx.h>

class GLOperator
{
public:
	GLOperator();
	~GLOperator();

public:
	//图形位置
	GLint spX, spY;

public:
	
	void processInput(GLFWwindow* window);

};

