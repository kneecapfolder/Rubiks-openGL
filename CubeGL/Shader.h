#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		// retrieve the source from file path
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			// read file's buffer content into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// close file handlers
			vShaderFile.close();
			fShaderFile.close();

			// convert stream to string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();



		// compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}



		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		// print linking arrow if any
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// delete linked shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// use/activate the shader
	void use()
	{
		glUseProgram(ID);
	}

	// utility uniform functions
	void setBool(const std::string& name, bool value) const
	{
		int location = glGetUniformLocation(ID, name.c_str());
		if (location == -1)
			std::cout << "Couldn't find uniform variable \"" << name.c_str() << "\"" << std::endl;

		glUniform1i(location, (int)value);
	}

	void setInt(const std::string& name, int value) const
	{
		int location = glGetUniformLocation(ID, name.c_str());
		if (location == -1)
			std::cout << "Couldn't find uniform variable \"" << name.c_str() << "\"" << std::endl;

		glUniform1i(location, value);
	}

	void setFloat(const std::string& name, float value) const
	{
		int location = glGetUniformLocation(ID, name.c_str());
		if (location == -1)
			std::cout << "Couldn't find uniform variable \"" << name.c_str() << "\"" << std::endl;

		glUniform1f(location, value);
	}

	void setVec2(const std::string& name, glm::vec2 value) const
	{
		int location = glGetUniformLocation(ID, name.c_str());
		if (location == -1)
			std::cout << "Couldn't find uniform variable \"" << name.c_str() << "\"" << std::endl;

		glUniform2fv(location, 1, glm::value_ptr(value));
	}

	void setVec3(const std::string& name, glm::vec3 value) const
	{
		int location = glGetUniformLocation(ID, name.c_str());
		if (location == -1)
			std::cout << "Couldn't find uniform variable \"" << name.c_str() << "\"" << std::endl;

		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void setMat4(const std::string& name, glm::mat4 value) const
	{
		int location = glGetUniformLocation(ID, name.c_str());
		if (location == -1)
			std::cout << "Couldn't find uniform variable \"" << name.c_str() << "\"" << std::endl;

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
};