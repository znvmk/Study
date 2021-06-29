#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture samplers
uniform sampler2D texture0;
uniform sampler2D texture1;
//物体光
uniform vec3 objectColor;
//环境光照
uniform vec3 ambientLightingColor;

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
	//FragColor = vec4(ambientLightingColor * objectColor,1.0);
	FragColor = vec4(ambientLightingColor * objectColor,1.0)*texture(texture0,TexCoord) * texture(texture1,TexCoord);
}