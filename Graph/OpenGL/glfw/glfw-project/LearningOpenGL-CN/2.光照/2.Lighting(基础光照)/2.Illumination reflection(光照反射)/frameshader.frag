#version 330 core
in vec3 FragPos;
in vec3 Normal;

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
	//ambient
	float ambientStrength = 0.1;
	vec3 ambient =ambientStrength * lightColor;

	//diffuse
	vec3 norm=normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength=0.5;
	vec3 camDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(camDir,reflectDir),0.0),64);
	vec3 specular = specularStrength * spec *lightColor;

	//sum
	vec3 result =(ambient + diffuse +specular) * objectColor;
	
	FragColor = vec4(result,1.0);
}