#pragma once
#include <glad/glad.h>
#include "Shader.h"

class Cube
{
public:

	glm::vec4 Position;
	glm::mat4 ModelMat;
	glm::mat4 RotMat;
	glm::mat4 OffsetMat;

	Cube(glm::vec3 startPosition) : Position(glm::vec4(startPosition, 1.0f)), ModelMat(glm::translate(glm::mat4(1.0f), glm::vec3(startPosition))), RotMat(glm::mat4(1.0f)), OffsetMat(glm::mat4(1.0f)), vertices{
		// positions		  // colors          // uv coords

		// back - green
		-0.5f, -0.5f, -0.5f,  0.435f, 0.910f, 0.439f,     0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.435f, 0.910f, 0.439f,     1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.435f, 0.910f, 0.439f,     1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.435f, 0.910f, 0.439f,     1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.435f, 0.910f, 0.439f,     0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.435f, 0.910f, 0.439f,     0.0f, 0.0f,

		// front - blue
  		-0.5f, -0.5f,  0.5f,  0.0235f, 0.5608f, 0.8039f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0235f, 0.5608f, 0.8039f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0235f, 0.5608f, 0.8039f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0235f, 0.5608f, 0.8039f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0235f, 0.5608f, 0.8039f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0235f, 0.5608f, 0.8039f,  0.0f, 0.0f,

		// left - red
  		-0.5f,  0.5f,  0.5f,  1.0, 0.3176, 0.3725,        1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0, 0.3176, 0.3725,        1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0, 0.3176, 0.3725,        0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0, 0.3176, 0.3725,        0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0, 0.3176, 0.3725,        0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0, 0.3176, 0.3725,        1.0f, 0.0f,

		// right - orange
  		 0.5f,  0.5f,  0.5f,  0.988f, 0.529f, 0.043f,     1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.988f, 0.529f, 0.043f,     1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.988f, 0.529f, 0.043f,     0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.988f, 0.529f, 0.043f,     0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.988f, 0.529f, 0.043f,     0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.988f, 0.529f, 0.043f,     1.0f, 0.0f,

		 // bottom
  		-0.5f, -0.5f, -0.5f,  1.0f, 0.894f, 0.396f,       0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.894f, 0.396f,       1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.894f, 0.396f,       1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.894f, 0.396f,       1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.894f, 0.396f,       0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.894f, 0.396f,       0.0f, 1.0f,

		// top
 		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,           0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,           1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,           1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,           1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,           0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,           0.0f, 1.0f
	}
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void Draw(Shader program)
	{
		program.use();
		program.setMat4("model", OffsetMat * ModelMat * RotMat);
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

private:
	float vertices[384];
	unsigned int VBO, VAO;

};