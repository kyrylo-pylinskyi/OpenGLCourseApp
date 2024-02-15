#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use() { glUseProgram(this->Program); }
	GLuint GetProgram() const { return Program; }

private:
	GLuint Program;
	std::string GetShaderSource(const GLchar* shaderPath);
	GLuint CreateShader(GLenum shaderType, const GLchar* shaderSource);
	void CreateProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif