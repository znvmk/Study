#pragma once
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


int main() {
	int width, height, nrChannels;
	//纹理会上下颠倒,这是因为OpenGL要求y轴0.0坐标是在图片的底部的，但是图片的y轴0.0坐标通常在顶部。
	//所以加上这一句设置图片从底部索引
	stbi_set_flip_vertically_on_load(true);

	//将图片加载到数组
	unsigned char* data = stbi_load("tes.jpg", &width, &height, &nrChannels, 0);
	//打印图片的前50个像素
	//像素点事3个为一组（RGB）,如果加上阿尔法通道（阿尔法通道（α Channel或Alpha Channel））则是四个为一组（RGBA）
	for (size_t i = 0; i < 50; i++)
	{
		std::cout << (int)data[i] << std::endl;
	}
	system("pause");

}
