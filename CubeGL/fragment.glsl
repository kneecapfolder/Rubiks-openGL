#version 330 core
out vec4 FragColor;

in vec3 VertexColor;
in vec2 TexCoords;

uniform sampler2D Texture;
// uniform sampler2D Texture2;

// uniform float mixVal;

void main()
{
	FragColor = texture(Texture, TexCoords) * vec4(VertexColor, 1.0f);
	// FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// FragColor =  mix(texture(Texture1, TexCoords), texture(Texture2, vec2(-TexCoords.s, TexCoords.t)), 0.2f);
	// FragColor = texture(ourTexture, TexCoords) * vec4(VertexColor, 1.0);
	// fragColor = vec4(vertexColor, 1.0f);
}