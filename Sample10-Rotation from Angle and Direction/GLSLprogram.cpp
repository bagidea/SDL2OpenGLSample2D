#include "GLSLprogram.h"

#include <fstream>
#include <vector>

GLSLprogram::GLSLprogram()
{
	id = 0;
	vertexId = 0;
	fragmentId = 0;
	numAttribute = 0;
}

GLSLprogram::~GLSLprogram()
{
	if(vertexId != 0)
		glDeleteShader(vertexId);

	if(fragmentId != 0)
		glDeleteShader(fragmentId);

	if(id != 0)
		glDeleteProgram(id);
}

void GLSLprogram::compileShaders(const string& vertexShaderFile, const string& fragmentShaderFile)
{
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	if(vertexId == 0)
		cout << "Create Vertex Shader Fail!" << endl;

	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	if(fragmentId == 0)
		cout << "Create Fragment Shader Fail!" << endl;

	compileShader(vertexShaderFile, vertexId);
	compileShader(fragmentShaderFile, fragmentId);
}

void GLSLprogram::linkShader()
{
	id = glCreateProgram();

	glAttachShader(id, vertexId);
	glAttachShader(id, fragmentId);

	glLinkProgram(id);

	GLint isLink = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &isLink);

	if(isLink == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		vector<char> errLog(maxLength);
		glGetProgramInfoLog(id, maxLength, &maxLength, &errLog[0]);

		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
		glDeleteProgram(id);

		printf("%s\n", &errLog[0]);
		cout << "Shader fail to link!" << endl;
	}
}

void GLSLprogram::addAttribute(const string& attributeName)
{
	glBindAttribLocation(id, numAttribute++, attributeName.c_str());
}

GLuint GLSLprogram::getUniformLocation(const string& uniformName)
{
	GLuint location = glGetUniformLocation(id, uniformName.c_str());

	if(location == GL_INVALID_INDEX)
		cout << "Uniform " << uniformName << " not found inshader!" << endl;

	return location;
}

void GLSLprogram::use()
{
	glUseProgram(id);
	
	for(int i = 0; i < numAttribute; i++)
		glEnableVertexAttribArray(i);
}

void GLSLprogram::unUse()
{
	glUseProgram(0);

	for(int i = 0; i < numAttribute; i++)
		glDisableVertexAttribArray(i);
}

void GLSLprogram::compileShader(const string& filePath, GLuint& id)
{
	ifstream file(filePath);	
	if(!file.is_open())
		cout << "Failed to Open : " << filePath << endl;

	string content = "";
	string line;

	while(file.good())
	{
		getline(file, line);
		content.append(line+"\n");
	}

	file.close();

	const char* contentPtr = content.c_str();

	glShaderSource(id, 1, &contentPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if(success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		vector<char> errLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errLog[0]);

		glDeleteShader(id);

		printf("%s\n", &errLog[0]);
		cout << "Shader fail compile!" << endl;
	}
}