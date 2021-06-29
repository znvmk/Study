#pragma once
#include"stdafx.h"

class GLDataProcessing
{
public:
	GLDataProcessing();
	~GLDataProcessing();

public:
	//图形位置
	GLint spX, spY;
	int step;

public:
	
	void processInput(GLFWwindow* window);
	void move();

};

