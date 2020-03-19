#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

int main() {
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans;
	// 矩阵初始化例子，如果使用的是0.9.9及以上版本,默认会是0矩阵。要添加参数
	// 上面这行代码就需要改为:
	glm::mat4 trans = glm::mat4(1.0f);

	//位移:x+1,y+1,z+0
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

	//旋转:沿Z轴旋转90度
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	vec = trans * vec;
	std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

	//放缩：每个轴放缩到0.5倍
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
	vec = trans * vec;
	std::cout << vec.x << " " << vec.y << " " << vec.z << std::endl;

	system("pause");
	return 0;
}
