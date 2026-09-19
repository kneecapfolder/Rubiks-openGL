#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"
#include "Cube.h"

const int WIN_WIDTH  = 800;
const int WIN_HEIGHT = 600;

void processInput(GLFWwindow* window);
unsigned int bindTexture(const char* texturePath, GLenum slot);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
template <typename Func>
void turn(Func condition);


float deltaTime = 0.0f;
float lastTime  = 0.0f;

std::vector<Cube> cubes;
std::vector<Cube*> selectedCubes;
float slideTimer = 0.0f;
float turnSpeedMult = 2.0f;
int counterClock = -1;
glm::vec3 turnAxis;
bool shiftDown = false;



int main()
{

	// configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// create window
	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "CubeGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glfwSetKeyCallback(window, key_callback);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	// camera
	Camera camera(glm::vec3(0.0f, 3.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -27.0f);
	glm::mat4 view  = camera.GetViewMatrix();
	glm::mat4 clip  = glm::perspective(glm::radians(camera.Zoom), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

	






	// Cube Shader Program
	Shader shader("vertex.glsl", "fragment.glsl");
	shader.use();
	shader.setMat4("view", view);
	shader.setMat4("projection", clip);
	bindTexture("cube-side.png", GL_TEXTURE0);
	shader.setInt("Texture", 0);
	shader.setVec3("LightColor", glm::vec3(1.0f));





	// Create Cubes
	cubes.reserve(26);

	cubes.emplace_back(glm::vec3(-1.0f,  1.0f, -1.0f));
	cubes.emplace_back(glm::vec3( 0.0f,  1.0f, -1.0f));
	cubes.emplace_back(glm::vec3( 1.0f,  1.0f, -1.0f));
	cubes.emplace_back(glm::vec3(-1.0f,  1.0f,  0.0f));
	cubes.emplace_back(glm::vec3( 0.0f,  1.0f,  0.0f));
	cubes.emplace_back(glm::vec3( 1.0f,  1.0f,  0.0f));
	cubes.emplace_back(glm::vec3(-1.0f,  1.0f,  1.0f));
	cubes.emplace_back(glm::vec3( 0.0f,  1.0f,  1.0f));
	cubes.emplace_back(glm::vec3( 1.0f,  1.0f,  1.0f));

	cubes.emplace_back(glm::vec3(-1.0f,  0.0f, -1.0f));
	cubes.emplace_back(glm::vec3( 0.0f,  0.0f, -1.0f));
	cubes.emplace_back(glm::vec3( 1.0f,  0.0f, -1.0f));
	cubes.emplace_back(glm::vec3(-1.0f,  0.0f,  0.0f));
	// skipped center (0,0,0)
	cubes.emplace_back(glm::vec3( 1.0f,  0.0f,  0.0f));
	cubes.emplace_back(glm::vec3(-1.0f,  0.0f,  1.0f));
	cubes.emplace_back(glm::vec3( 0.0f,  0.0f,  1.0f));
	cubes.emplace_back(glm::vec3( 1.0f,  0.0f,  1.0f));

	cubes.emplace_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	cubes.emplace_back(glm::vec3( 0.0f, -1.0f, -1.0f));
	cubes.emplace_back(glm::vec3( 1.0f, -1.0f, -1.0f));
	cubes.emplace_back(glm::vec3(-1.0f, -1.0f,  0.0f));
	cubes.emplace_back(glm::vec3( 0.0f, -1.0f,  0.0f));
	cubes.emplace_back(glm::vec3( 1.0f, -1.0f,  0.0f));
	cubes.emplace_back(glm::vec3(-1.0f, -1.0f,  1.0f));
	cubes.emplace_back(glm::vec3( 0.0f, -1.0f,  1.0f));
	cubes.emplace_back(glm::vec3( 1.0f, -1.0f,  1.0f));

	// light source
	glm::vec3 lightPos(3.0f);
	float iconPlane[] = {
		// vertex position    // uv coords
		-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
	};

	unsigned int planeVBO, planeVAO;
	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);

	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(iconPlane), iconPlane, GL_STATIC_DRAW);
	// vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// side colors
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader lightSourceShader("sourceV.glsl", "sourceF.glsl");
	lightSourceShader.use();
	lightSourceShader.setMat4("view", view);
	lightSourceShader.setMat4("projection", clip);
	bindTexture("lightsource.png", GL_TEXTURE1);
	lightSourceShader.setInt("Texture", 1);


	// Background
	//float bgVerts[] = {
	//	-1.0f,  1.0f, 1.0f,
	//	 1.0f,  1.0f, 1.0f,
	//	-1.0f, -1.0f, 1.0f,

	//	-1.0f, -1.0f, 1.0f,
	//	 1.0f, -1.0f, 1.0f,
	//	 1.0f,  1.0f, 1.0f,
	//};

	//unsigned int bgVBO, bgVAO;
	//glGenVertexArrays(1, &bgVAO);
	//glBindVertexArray(bgVAO);
	//
	//glGenBuffers(1, &bgVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(bgVerts), bgVerts, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//Shader bgProgram("bgv.glsl", "bgf.glsl");
	//bgProgram.use();


	// render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window);


		// animated turn
		if (slideTimer > 0.0f)
		{
			deltaTime *= turnSpeedMult;
			slideTimer -= deltaTime;
			
			// finish turn
			if (slideTimer < 0.0f) 
			{
				deltaTime += slideTimer;
				for (Cube* cube : selectedCubes)
				{
					cube->OffsetMat = glm::mat4(1.0f);
					cube->RotMat = glm::rotate(glm::mat4(1.0f), (float)glm::radians(90.0f * counterClock), turnAxis) * cube->RotMat;
					cube->ModelMat = glm::translate(glm::mat4(1.0f), glm::vec3(cube->Position));
				}
			}
			else
				for (Cube* cube : selectedCubes)
					cube->OffsetMat = glm::rotate(cube->OffsetMat, (float)glm::radians(90.0f * counterClock * deltaTime), turnAxis);
		}


		lightPos.x = 2.25f * cos(glm::radians(glfwGetTime() * 100.0f));
		lightPos.y = 2.0f + 0.3f * sin(glm::radians(glfwGetTime() * 100.0f));
		//lightPos.z = 3.0f * sin(glm::radians(glfwGetTime() * 50.0f));

		//lightPos.x = 1.5f;
		//lightPos.y = 2.0f;
		lightPos.z = 2.0f;




		// render background
		/*glDisable(GL_DEPTH_TEST);
		bgProgram.use();
		glBindVertexArray(bgVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);*/


		// render light source
		glBindVertexArray(planeVAO);
		lightSourceShader.use();
		lightSourceShader.setMat4("model", glm::translate(glm::mat4(1.0f), lightPos));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// render cubes
		//glEnable(GL_DEPTH_TEST);
		shader.use();
		shader.setVec3("lightPos", lightPos);
		for (Cube &cube : cubes)
			cube.Draw(shader);




		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	shiftDown = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
}


unsigned int bindTexture(const char* texturePath, GLenum slot)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// load image 1
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	return texture;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (slideTimer > 0.0f)
		return;





	if (key == GLFW_KEY_U && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		counterClock = 1;

		turn([](glm::vec3 pos) {
			return pos.y == 1.0f;
		});
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		counterClock = -1;

		turn([](glm::vec3 pos) {
			return pos.y == -1.0f;
			});
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		counterClock = 1;

		turn([](glm::vec3 pos) {
			return pos.x == 1.0f;
			});
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		counterClock = -1;

		turn([](glm::vec3 pos) {
			return pos.x == -1.0f;
			});
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		counterClock = 1;

		turn([](glm::vec3 pos) {
			return pos.z == 1.0f;
			});
	}

	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		counterClock = -1;

		turn([](glm::vec3 pos) {
			return pos.z == -1.0f;
			});
	}

	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		counterClock = -1;

		turn([](glm::vec3 pos) {
			return pos.x == 0.0f;
			});
	}

	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		counterClock = -1;

		turn([](glm::vec3 pos) {
			return pos.y == 0.0f;
			});
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		counterClock = 1;

		turn([](glm::vec3 pos) {
			return pos.z == 0.0f;
			});
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(1.0f, 0.0f, 0.0f);
		counterClock = 1;

		turn([](glm::vec3 pos) {
			return true;
			});
	}

	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(0.0f, 1.0f, 0.0f);
		counterClock = 1;

		turn([](glm::vec3 pos) {
			return true;
			});
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		turnAxis = glm::vec3(0.0f, 0.0f, 1.0f);
		counterClock = 1;

		turn([](glm::vec3 pos) {
			return true;
			});
	}
}

template <typename Func>
void turn(Func condition)
{
	selectedCubes.clear();
	counterClock *= (shiftDown ? 1 : -1);

	for (Cube& cube : cubes)
		if (condition(cube.Position))
		{
			//std::cout << cube.Position.x << ", " << cube.Position.y << ", " << cube.Position.z << std::endl;
			cube.Position = glm::round(glm::rotate(glm::mat4(1.0f), (float)glm::radians(90.0f * counterClock), turnAxis) * cube.Position);
			selectedCubes.push_back(&cube);
			//std::cout << cube.Position.x << ", " << cube.Position.y << ", " << cube.Position.z << std::endl;
			//std::cout << std::endl;
		}

	slideTimer = 1.0f;
}