#version 330 core
struct Material
{
	sampler2D diffuse; // 漫反射贴图
	sampler2D specular; // 镜面光贴图
	sampler2D refTex; // 发射光贴图
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;// 片段位置
in vec3 Normal_Frag;// 片段法向量
in vec2 TexCoords;// 纹理坐标
in vec3 color;


//材质
uniform Material material;
uniform Light light;

uniform vec3 objectColor; // 物体颜色
uniform vec3 lightColor; // 光源颜色
uniform vec3 lightPos; // 光源位置
uniform vec3 viewPos; // 视角位置也就是相机的位置

out vec4 FragColor;


// 计算漫反射的函数
vec3 diffLight(vec3 normalVector) {
	float diff;
	vec3 lightDir = normalize(lightPos - FragPos);
	diff = max(dot(normalVector,lightDir),0.0);
	vec3 res;
	res = diff * texture(material.diffuse,TexCoords).rgb * lightColor * light.diffuse + texture(material.refTex,TexCoords).rgb;
	return res;
} 
// 镜面反射光计算
vec3 mirrorLight(vec3 normalVector) {
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,normalVector);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	//反射光太强烈
	return spec * texture(material.specular,TexCoords).rgb * lightColor * light.specular ;//+ texture(material.refTex,TexCoords).rgb;
	//
}

// 环境光计算
vec3 ambientLight() {
    vec3 res;
	//反射光太强烈
	res = lightColor * light.ambient * texture(material.diffuse,TexCoords).rgb ;//+ texture(material.refTex,TexCoords).rgb;
	
	return res;
}

void main()
{
	//ambient:环境光
	vec3 normalVector = normalize(Normal_Frag);
	//diffuse:漫反射
	vec3 diff = diffLight(normalVector);
	//specular：镜面光
	vec3 mirror = mirrorLight(normalVector);
	//phoneLight冯氏光照
	vec3 phoneLight = ambientLight() + diff + mirror;

	FragColor = vec4(phoneLight,1.0);
}