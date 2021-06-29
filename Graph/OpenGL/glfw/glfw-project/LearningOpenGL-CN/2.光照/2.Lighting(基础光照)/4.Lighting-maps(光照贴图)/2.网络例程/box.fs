#version 330 core
in vec3 color;
out vec4 fragColor;
uniform vec3 objectColor; // 物体颜色
uniform vec3 lightColor; // 光源颜色
uniform vec3 lightPos; // 光源位置
uniform vec3 viewPos; // 视角位置也就是相机的位置
in vec3 fragPos; // 片段位置
in vec3 normal_frag; // 片段法向量
in vec2 atextcoord; // 纹理坐标
struct Material {
	sampler2D diffuse; // 漫反射贴图
	sampler2D specular; // 镜面光贴图
	sampler2D refTex; // 发射光贴图
	float shininess;
};
struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 position;
	vec3 specular;
};
uniform Material material;
uniform Light light;
// 计算漫反射的函数
vec3 diffLight(vec3 normalVector) {
	float diff;
	vec3 lightDir = normalize(lightPos - fragPos);
	diff = max(dot(normalVector,lightDir),0.0);
	vec3 res;
	res = diff * vec3(texture(material.diffuse,atextcoord)) * lightColor * light.diffuse + vec3(texture(material.refTex,atextcoord));
	return res;
} 
// 镜面反射光计算
vec3 mirrorLight(vec3 normalVector) {
	vec3 lightDir = normalize(lightPos - fragPos);
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir,normalVector);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	return spec * (vec3(texture(material.specular,atextcoord))) * lightColor * light.specular + vec3(texture(material.refTex,atextcoord));
}
// 环境光计算
vec3 ambientLight() {
    vec3 res;
	res = lightColor * light.ambient * vec3(texture(material.diffuse,atextcoord)) + vec3(texture(material.refTex,atextcoord));
	return res;
}
void main() {
	vec3 normalVector = normalize(normal_frag);
	vec3 diff = diffLight(normalVector);
	vec3 mirror = mirrorLight(normalVector);
	vec3 phoneLight = ambientLight() + diff + mirror;
	fragColor = vec4(phoneLight,1.0);
}