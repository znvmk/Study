#pragma once
#include<stdafx.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include<gloperator.h>



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


#pragma region Model Data
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
#pragma endregion

#pragma region Init Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float fov = 45.0f;

int kenu = 0;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
#pragma endregion

//函数声明
#pragma region Function Declaration
//跟随窗口大小，动态改变图形大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLuint LoadImageToGPU(const char* imagename, GLint internalformat, GLenum format, int textureSlot);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
#pragma endregion


int main() 
{
    GLOperator glo;

    #pragma region Init Window
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
#pragma endregion

    //shader class
    Shader ourShader("vertexshader.vs", "frameshader.fs");

    glViewport(0, 0, 1000, 1000);
   
    //****/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //设置属性
    #pragma region GLFW Attribute

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    // 关掉鼠标
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //打开面剔除
   // glEnable(GL_CULL_FACE);
    //剔除背面
   // glCullFace(GL_BACK);

     //框线模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#pragma endregion

    //顶点
    #pragma region VAO-VBO-EBO
    //VAO:顶点数组对象
    //VBO:顶点缓冲对象
    //EBO:索引缓冲对象
    //将创建的顶点对象绑定，流程是:
    //1.创建顶点对象（顶点对象可以理解为一个数组指针）
    //2.将顶点对象（指针）与数组绑定（指针指向一个1*1的一个数组）
    //3.将已经绑定好数组得顶点对象，再绑定到设备等待渲染
    GLuint VAO, VBO,EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
   
    //绑定
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //缓冲
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //设置顶点属性
    //顶点数据解析方式
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //颜色属性
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    //纹理坐标属性
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
#pragma endregion
    
    //贴图
    #pragma region LoadTexture
    //texture:纹理贴图
    GLuint texture0, texture1;
    //*****绑定纹理
    //texture0
    texture0 = LoadImageToGPU("texture.jpg", GL_RGB, GL_RGB, 0);
    //texture1
    texture1 = LoadImageToGPU("smiling-face.jpg", GL_RGB, GL_RGB, 1);
    //texture1 = LoadImageToGPU("smiling-face.png", GL_RGBA, GL_RGBA, 1);
#pragma endregion   


    #pragma region prepare MVP matrices
    //glm transform
    //glm::mat4 trans;
    // 矩阵初始化例子，如果使用的是0.9.9及以上版本,默认会是0矩阵。要添加参数
    // 上面这行代码就需要改为:
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 modelMat = glm::mat4(1.0f);
    glm::mat4 viewMat = glm::mat4(1.0f);
    glm::mat4 projMat = glm::mat4(1.0f);
    
    modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //获取Camera
    viewMat = camera.GetViewMatrix();
    //projMat = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    projMat = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
#pragma endregion


	//随用户改变窗口，改变视口大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//窗口消息循环
	while (!glfwWindowShouldClose(window))
	{
        //渲染指令
        glClearColor(0.0f, 0.0f, 0.0f, 10.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //glViewport(0, 0, 800, 800);

        //获取Camera
        viewMat = camera.GetViewMatrix();
		//按键消息循环,输入
		glo.processInput(window);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //按键消息循环,输入
        processInput(window);

        Camera ca(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);

        //图形变换
        #pragma region graph trasform
        //glm transform
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
        #pragma endregion     

        // 在绑定纹理之前先激活纹理单元
        glActiveTexture(GL_TEXTURE0);
        //绑定纹理
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        //绑定到顶点数组
        glBindVertexArray(VAO);

        
        

        for (int i = 0; i < 10; i++)
        {
            glm::mat4 modelMat1 = glm::mat4(1.0f);
            modelMat1 = glm::translate(modelMat1, cubePositions[i]);
            float angle = 20.0f * i;
            modelMat1 = glm::rotate(modelMat1, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            //使用着色器
            ourShader.use();

            //设置材质
            //绑定纹理单元
            glUniform1i(glGetUniformLocation(ourShader.ID, "texture0"), 0);
            glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 1);//手动绑定
            //ourShader.setInt("texture2", 1);//使用着色器类设置

            //使用材质
            glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat1));
            //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            
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

//函数定义
#pragma region Funcation Definition
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLuint LoadImageToGPU(const char* imagename, GLint internalformat, GLenum format, int textureSlot)
{
    //设置从底部度图片数据，不然图片会上下颠倒
    stbi_set_flip_vertically_on_load(true);

    GLuint TexBuffer;

    //**注意是Textures，不是Buffers
    glGenTextures(1, &TexBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);

    //纹理加载保存数组
    int width, height, nrChannels;
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //加载图片
    //图片大小必须是2的n次幂，不然图像会变成灰色条纹
    unsigned char* data = stbi_load(imagename, &width, &height, &nrChannels, 0);
    // 使用已加载的纹理数组生成纹理
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    //释放数组空间
    stbi_image_free(data);

    return TexBuffer;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout <<"xops: "<< xpos << ","<<"ypos: " << ypos << std::endl;
    if (firstMouse)
    {
        //lastX = xpos;
        //lastY = ypos;
        lastX = SCR_HEIGHT;
        lastY = SCR_WIDTH/2;
        firstMouse = false;
    }
    
    float xoffset = lastX - xpos;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch -= yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    camera.Front = cameraFront;
}

//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}

void processInput(GLFWwindow* window)
{
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
        kenu++;
        std::cout << " I keydown:" <<kenu<< std::endl;

    }
        
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
#pragma endregion