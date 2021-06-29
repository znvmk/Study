#version 330 core
in vec3 FragPos;
in vec3 Normal;

//in vec3 ourColor;
//in vec2 TexCoord;

// texture samplers
//uniform sampler2D texture0;
//uniform sampler2D texture1;
//物体光
uniform vec3 objectColor;
//环境光照
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;


out vec4 FragColor;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = texture(texture0, TexCoord) * vec4(ourColor, 1.0);
	//混合方式
	//FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.2);
	//FragColor = texture(texture0,TexCoord) * texture(texture1,TexCoord);
	//FragColor = texture(texture0,TexCoord) + texture(texture1,TexCoord);
	//FragColor = texture(texture0,TexCoord) - texture(texture1,TexCoord);
	//FragColor = texture(texture0,TexCoord) / texture(texture1,TexCoord);
	//FragColor = vec4(ambientColor * objectColor,1.0);
	//FragColor = vec4(ambientColor * objectColor,1.0)*texture(texture0,TexCoord) * texture(texture1,TexCoord);
	vec3 lightDir = normalize(lightPos - FragPos);

	//vec3 diffuse = dot(lightDir,Normal) * lightColor * objectColor;
	//FragColor = vec4(diffuse,1.0);
	//设置最小为零：在点乘结果和零对比求最大值，即结果最小为零，结果不为负数；相反，两者之间求最小值，即最大为设定的值
	vec3 diffuse = max(dot(lightDir,Normal),0) * lightColor;
	FragColor = vec4((ambientColor + diffuse) * objectColor,1.0);
}