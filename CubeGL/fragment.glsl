#version 330 core
out vec4 FragColor;

in vec3 VertexColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

uniform sampler2D Texture;
uniform vec3 LightColor;

void main()
{
	// ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * LightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff * LightColor;

	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectedDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectedDir), 0.0), 32);
	vec3 specular = spec * specularStrength * LightColor;


	//FragColor = vec4(1.0);
	FragColor = texture(Texture, TexCoords) * vec4((ambient + diffuse + specular) * VertexColor, 1.0);
}