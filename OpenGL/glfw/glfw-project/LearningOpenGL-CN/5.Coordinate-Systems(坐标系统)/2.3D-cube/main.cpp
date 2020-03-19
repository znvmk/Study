#pragma once
#include<stdafx.h>
#include<gloperator.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"




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
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    GLuint indices[] = {
        0,1,3,//第一个三角形
        1,2,3//第二个三角形
    };

    //纹理加载保存数组
    int width, height, nrChannels;

    //设置从底部度图片数据，不然图片会上下颠倒
    stbi_set_flip_vertically_on_load(true);
   

    //VAO:顶点数组对象
    //VBO:顶点缓冲对象
    //EBO:索引缓冲对象
    //texture:纹理贴图
    GLuint VAO, VBO,EBO,texture0,texture1;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //**注意是Textures，不是Buffers
    glGenTextures(1, &texture0);
    glGenTextures(1, &texture1);

    //绑定
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //*****绑定纹理
    //texture0
    glBindTexture(GL_TEXTURE_2D, texture0);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载图片
    //图片大小必须是2的n次幂，不然图像会变成灰色条纹
    unsigned char* data = stbi_load("texture.png", &width, &height, &nrChannels, 0);
    // 使用已加载的纹理数组生成纹理
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放数组空间
    stbi_image_free(data);

    //texture1
    glBindTexture(GL_TEXTURE_2D, texture1);
    //用纹理加载数组生成纹理
   // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("smiling-face.png", &width, &height, &nrChannels, 0);
    // 使用已加载的纹理数组生成纹理
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放数组空间
    stbi_image_free(data);
    
   

    //缓冲
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnable(GL_COLOR_MATERIAL);

    



    //设置顶点属性
    //顶点数据解析方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //纹理坐标属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    

    



    
    //框线模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);




     //使用着色器
    ourShader.use();
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture0"), 0);
    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 1);//手动绑定
    //ourShader.setInt("texture2", 1);//使用着色器类设置

    //glm transform

    //glm::mat4 trans;
    // 矩阵初始化例子，如果使用的是0.9.9及以上版本,默认会是0矩阵。要添加参数
    // 上面这行代码就需要改为:
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 modelMat = glm::mat4(1.0f);
    glm::mat4 viewMat = glm::mat4(1.0f);
    glm::mat4 projMat = glm::mat4(1.0f);

    //GLuint transformLoc = glGetUniformLocation(ourShader.ID, "transform");
    modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
    projMat = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


	//随用户改变窗口，改变视口大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//窗口消息循环
	while (!glfwWindowShouldClose(window))
	{
		//按键消息循环,输入
		glo.processInput(window);

        //glm transform
    //*
    //glm::mat4 trans;
    // 矩阵初始化例子，如果使用的是0.9.9及以上版本,默认会是0矩阵。要添加参数
    // 上面这行代码就需要改为:
        glm::mat4 trans = glm::mat4(1.0f);
        GLuint transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        
      
        //变换
        //位移
        if (glo.transKey)
           trans = glm::translate(trans, glm::vec3(glo.transX, glo.transY, glo.transZ));
        
        //旋转
        if (glo.roateKey) {
            //旋转:沿X轴旋转
            trans = glm::rotate(trans, glm::radians(glo.roateX), glm::vec3(1.0f, 0.0f, 0.0f));
            //旋转:沿Y轴旋转
            trans = glm::rotate(trans, glm::radians(glo.roateY), glm::vec3(0.0f, 1.0f, 0.0f));
            //旋转:沿Z轴旋转
            trans = glm::rotate(trans, glm::radians(glo.roateZ), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        //放缩
        if(glo.scaleKey)
            trans = glm::scale(trans, glm::vec3(glo.scaleX, glo.scaleY, glo.scaleZ));
          
        //按获取的时间旋转
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //*/
        glViewport(0,0, 1000, 1000);

		//渲染指令
		glClearColor(0.0f, 0.0f, 0.0f, 10.0f);
		glClear(GL_COLOR_BUFFER_BIT);

       
        glActiveTexture(GL_TEXTURE0);// 在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

       

        //使用着色器
        ourShader.use();
        //glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
        //ourShader.setInt("texture2", 1);
        //glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
        //glUniform1i(glGetUniformLocation(ourShader.ID, "texture2"), 1);
        
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        
		//检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
    //释放缓冲
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &texture0);
    glDeleteBuffers(1, &texture1);

	glfwTerminate();
	return 0;
	
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}