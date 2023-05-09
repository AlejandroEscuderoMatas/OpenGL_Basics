#pragma once
# define GLAD_ONLY_HEADERS
# include "common.h"

class Shader
{
public:
	unsigned int idShader = -1;
	std::string fileName = "";
	GLenum type = -1;
	std::string source = "";

	Shader(std::string fileName);
	void readSource();
	void compileShader();
	void checkErrors();
	void clean();
};