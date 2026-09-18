#version 330 core

out vec4 FragColor;

in vec3 vertexPos;

void main()
{
	// bool c = int((vertexPos.x + 1) * 10 + int((vertexPos.y + 1) * 10) % 2) % 2 == 1;

	// FragColor = vec4(c ? 0 : 0.5f, 0, 0, 1.0f);
	FragColor = vec4(vertexPos, 1.0f);
	// FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// FragColor =  mix(texture(Texture1, TexCoords), texture(Texture2, vec2(-TexCoords.s, TexCoords.t)), 0.2f);
	// FragColor = texture(ourTexture, TexCoords) * vec4(VertexColor, 1.0);
	// fragColor = vec4(vertexColor, 1.0f);
}