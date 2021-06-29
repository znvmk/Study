#pragma once
#include"stdafx.h"

class GLDataProcessing
{
public:
	GLDataProcessing();
	~GLDataProcessing();

public:

	//key:t,z,s,r,
	//平移translation
	GLboolean transKey;
	GLfloat transX, transY, transZ;

	//旋转
	GLboolean roateKey;
	//旋转坐标
	GLfloat roateX, roateY, roateZ;
	
	//放缩
	GLboolean scaleKey;
	//放缩左边
	GLfloat scaleX, scaleY, scaleZ;

	//变化Z轴开关
	GLboolean zKey;

	
	//按键档位开关
	GLboolean shiftKey;

public:
	
	void processInput(GLFWwindow* window);

};

