#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec3 VertexColor;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	// gl_Position = pipeLine * vec4(aPos, 1.0);
	TexCoords = aTexCoords;

	// Normal = mat3(transpose(inverse(view * model))) * aNormal;
	// FragPos = vec3(view * model * vec4(aPos, 1.0));
	// LightPos = vec3(view * vec4(lightPos, 1.0));
}