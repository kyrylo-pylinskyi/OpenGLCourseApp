#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../include/Shaders/Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	std::string vertexShaderSource = GetShaderSource(vertexPath);
	std::string fragmentShaderSource = GetShaderSource(fragmentPath);

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

	CreateProgram(vertexShader, fragmentShader);
}

std::string Shader::GetShaderSource(const GLchar* shaderPath)
{
	std::string shaderSource;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::badbit);
	try {
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderSource = shaderStream.str();
	}
	catch (std::ifstream::failure e) {
		printf("ERROR::SHADER::FILE_READ_FAILED\nFile Name: %s\n%s\n", shaderPath, e.what());
	}

	return shaderSource;
}

GLuint Shader::CreateShader(GLenum shaderType, const GLchar* shaderSource)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT", infoLog);
	}

	return shader;
}

void Shader::CreateProgram(GLuint vertexShader, GLuint fragmentShader)
{
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertexShader);
	glAttachShader(this->Program, fragmentShader);
	glLinkProgram(this->Program);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, sizeof(infoLog), NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
