#version 330 core
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	//sampler2D diffuse;
	//sampler2D specular;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


//材质
uniform Material material;

//光照
uniform Light light;

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
	//vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
	vec3 ambient = light.ambient * material.ambient * ambientColor * lightColor;
	//vec3 ambient =texture(material.diffuse, TexCoords).rgb;
	//vec3 ambient=material.ambient*ambientColor;
	
	//diffuse:漫反射
	vec3 norm=normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = lightDir * light.diffuse * material.diffuse * diff;
	//vec3 diffuse=light.diffuse * diff * texture(material.diffuse,TexCoords).rgb;
	
	//specular：镜面光
	vec3 camDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(reflectDir,camDir),0.0), material.shininess);
	//vec3 specular = light.specular * texture(material.specular , TexCoords).rgb  * spec * lightColor;
	vec3 specular = light.specular * material.specular * spec * lightColor;

	//sum
	vec3 result =(ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result,1.0);
}