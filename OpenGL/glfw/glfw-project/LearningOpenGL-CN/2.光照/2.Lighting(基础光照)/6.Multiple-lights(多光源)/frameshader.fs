#version 330 core
struct Material
{
	sampler2D diffuse; // 漫反射贴图
	sampler2D specular; // 镜面光贴图
	sampler2D refTex; // 发射光贴图（自发光）
	float shininess;
};
//定向光，平行光
struct DirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//点光
struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//聚光投影
struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 4

in vec3 FragPos;// 片段位置
in vec3 Normal;// 片段法向量
in vec2 TexCoords;// 纹理坐标

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform vec3 viewPos;//视角（摄像机）位置
uniform vec3 objectColor;
out vec4 FragColor;

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir);
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir);

void main()
{
		//propreties
		vec3 norm=normalize(Normal);
		vec3 viewDir =normalize(viewPos - FragPos);

		 vec3 result = CalcDirLight(dirLight,norm,viewDir);
		 //for(int i=0;i<NR_POINT_LIGHTS;i++)
		result = CalcPointLight(pointLights[0],norm,FragPos,viewDir);
		result += CalcPointLight(pointLights[1],norm,FragPos,viewDir);
		result += CalcPointLight(pointLights[2],norm,FragPos,viewDir);
		result += CalcPointLight(pointLights[3],norm,FragPos,viewDir);
		result += CalcSpotLight(spotLight,norm,FragPos,viewDir);

		//vec3 result = CalcSpotLight(spotLight,norm,FragPos,viewDir);


		FragColor =vec4(result,1.0);
}

vec3 CalcDirLight(DirLight light , vec3 normal , vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	//diffuse shading
	float diff = max(dot(normal , lightDir) , 0.0);
	//specular shading
	vec3 reflectDir = reflect(-lightDir , normal);
	float spec = pow(max(dot(viewDir , reflectDir) , 0.0),material.shininess);
	//combine results
	vec3 ambient =light.ambient * vec3(texture(material.diffuse,TexCoords));
	vec3 diffuse =light.diffuse * diff * vec3(texture(material.diffuse , TexCoords));
	vec3 specular =light.specular * spec * vec3(texture(material.specular , TexCoords));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir)
{
	vec3 lightDir = normalize(light.position -fragPos);
	//diffuse shading
	float diff = max(dot(normal,lightDir),0.0);
	//specular
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0) , material.shininess);
	//attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance *distance));
	//combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse , TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse , TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular , TexCoords));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ((ambient + diffuse + specular) + light.color);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
