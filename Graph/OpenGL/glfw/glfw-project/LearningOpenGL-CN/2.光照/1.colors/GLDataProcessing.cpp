#include "GLDataProcessing.h"

GLDataProcessing::GLDataProcessing()
{
    transKey = 1;
    transX = transY = transZ = 0.0f;

    roateKey = 0;
    roateX = roateY = roateZ = 0.0f;

    scaleKey = 0;
    scaleX = scaleY = scaleZ = 1.0f;

    zKey = 0;

    shiftKey = 0;
}
GLDataProcessing::~GLDataProcessing()
{

}


/*

action 按键动作
GLFW_RELEASE 松开
GLFW_PRESS 按下
GLFW_REPEAT 重复，一直按着
mods 按键模式
GLFW_MOD_SHIFT 按下Shift键
GLFW_MOD_CONTROL 按下Ctrl键
GLFW_MOD_ALT 按下Alt键
GLFW_MOD_SUPER
*/
void GLDataProcessing::processInput(GLFWwindow* window)
{
    //Esc关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (!zKey)
        {
            //平移
            if (transKey)
            {
                transY += 0.001;
                return;
            }
            //旋转
            if (roateKey)
            {
                if (roateY >= 360.0 || roateY <= -360.0)
                    roateY = 0.0;

                roateY += 0.1;
                return;
            }
            //放缩
            if (scaleKey)
            {
                if (scaleY >= 10 || scaleY < 1.0)
                    scaleY = 1.0;
                scaleY += 0.001;
            }
        }

        if (zKey)
        {
            //平移
            if (transKey)
            {
                transZ += 0.0001;
                return;
            }

            //旋转
            if (roateKey)
            {
                if (roateZ >= 360.0 || roateZ <= -360.0)
                    roateZ = 0.0;

                roateZ += 0.1;
                return;
            }
            //放缩
            if (scaleKey)
            {
                if (scaleZ >= 10 || scaleZ < 1.0)
                    scaleZ = 1.0;
                scaleZ += 0.001;
            }
        }
        
       

        return;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (!zKey)
        {
            //平移
            if (transKey)
            {
                transY -= 0.001;
                return;
            }
            //旋转
            if (roateKey)
            {
                if (roateY >= 360.0 || roateY <= -360.0)
                    roateY = 0.0;

                roateY -= 0.1;
                return;
            }
            //放缩
            if (scaleKey)
            {
                if (scaleY >= 10 || scaleY < 0.0)
                    scaleY = 1.0;
                scaleY -= 0.001;
            }
        }
        if (zKey)
        {
            //平移
            if (transKey)
            {
                transZ -= 0.001;
                return;
            }
            //旋转
            if (roateKey && zKey)
            {
                if (roateZ >= 360.0 || roateZ <= -360.0)
                    roateZ = 0.0;

                roateZ -= 0.1;
                return;
            }
            //放缩
            if (scaleKey)
            {
                if (scaleZ >= 10 || scaleZ < 0.0)
                    scaleZ = 1.0;
                scaleZ -= 0.001;
            }
        }
        

        
        
        return;
    } 
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        //平移
        if (transKey) transX -= 0.001;

        //旋转
        if (roateKey)
        {
            if (roateX >= 360.0 || roateX <= -360.0)
                roateX = 0.0;

            roateX -= 0.1;
            return;
        }
        //放缩
        if (scaleKey)
        {
            if (scaleX >= 10 || scaleX < 0.0)
                scaleX = 1.0;
            scaleX -= 0.001;
        }
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        //平移
        if (transKey) transX += 0.001;

        //旋转
        if (roateKey)
        {
            if (roateX >= 360.0 || roateX <= -360.0)
                roateX = 0.0;

            roateX += 0.1;
            return;
        }
       
        //放缩
        if (scaleKey)
        {
            if (scaleX >= 10 || scaleX < 1.0)
                scaleX = 1.0;
            scaleX += 0.001;
        }

        return;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        roateKey = 1;
        transKey = 0;
        scaleKey = 0;
        
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        roateKey = 0;
        transKey = 1;
        scaleKey = 0;
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        roateKey = 0;
        transKey = 0;
        scaleKey = 1;

        return;
    }
    
    if (glfwGetKey(window, GLFW_KEY_Z) ==GLFW_PRESS)
    {
        if (shiftKey) zKey = 1;
        else zKey = 0;
        
        return;
    }
    
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        
        
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        shiftKey = 0;
        return;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        shiftKey = 1;
        return;
    }
}
