#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include <iostream>
#include <string>
#include <GL\glew.h>

using namespace std;

class GLSLprogram
{
public:
	GLSLprogram();
	~GLSLprogram();

	void compileShaders(const string& vertexShaderFile, const string& fragmentShaderFile);
	void linkShader();
	void addAttribute(const string& attributeName);

	GLuint getUniformLocation(const string& uniformName);

	void use();
	void unUse();
private:
	void compileShader(const string& filePath, GLuint& id);

	GLuint id;
	GLuint vertexId;
	GLuint fragmentId;

	int numAttribute;
};

#endif