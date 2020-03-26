#version 330 core
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 FragPos;
in vec3 Normal;


//材质
uniform Material material;
//物体光
uniform vec3 objectColor;
//环境光照
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;

void main()
{
	//ambient:环境光
	vec3 ambient =material.ambient * lightColor;


	//diffuse:漫反射
	vec3 norm=normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = material.diffuse * diff * lightColor;

	//specular：镜面光
	vec3 camDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(camDir,reflectDir),0.0),material.shininess);
	vec3 specular = material.specular * spec *lightColor;

	//sum
	vec3 result =(ambient + diffuse +specular) * objectColor;
	FragColor = vec4(result,1.0);
}