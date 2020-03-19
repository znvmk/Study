#pragma once
#include<iostream>
#include<shader.h>
#include<stdafx.h>
#include<gloperator.h>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() 
{
    GLOperator glo;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本，即3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	
    //shader class
    Shader ourShader("3.3.shader.vs", "3.3.shader.fs");




	//glViewport(0, -100, 500, 500);

    //打开面剔除
   // glEnable(GL_CULL_FACE);
    //剔除背面
   // glCullFace(GL_BACK);


    float vertices[] = {
        //第一个三角形
        0.4f,0.8f,0.0f,1.0f,0.0f,0.0f,//右上
        0.8f,0.0f,0.0f,0.0f,1.0f,0.0f,//右下
        //去掉重复占用资源的边，即画了两边的对角线
        0.0f,0.0f,0.0f,0.0f,0.0f,1.0f//左上
        
    };
    GLuint indices[] = {
        0,1,3,//第一个三角形
        1,2,3//第二个三角形
    };
    //VAO:顶点数组对象
    //VBO:顶点缓冲对象
    //EBO:索引缓冲对象
    GLuint VAO, VBO,EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //绑定
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    //位置属性
    //顶点数据解析方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

   

    // uncomment this call to draw in wireframe polygons.
    //框线模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);







	//随用户改变窗口，改变视口大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//窗口消息循环
	while (!glfwWindowShouldClose(window))
	{
		//按键消息循环,输入
		glo.processInput(window);
        glViewport(glo.spX,glo.spY, 1000, 1000);

		//渲染指令
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        
        //使用着色器
        ourShader.use();

        //使用顶点缓冲对象方式绘制四边形（两个三角形拼接而成）
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //使用索引缓冲对象方式绘制三角形
        //可防止绘制因两个三角形拼接而造成绘制两次四边形对角线的开销浪费
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
	
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}