#include "gloperator.h"

GLOperator::GLOperator()
{
	spX = 0;
	spY = 0;
}
GLOperator::~GLOperator()
{

}

void GLOperator::processInput(GLFWwindow* window)
{
    //Esc关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        spY += 1;
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        spY -= 1;
        return;
    } 
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        spX -= 1;
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        spX += 1;
        return;
    }
       
    
}
