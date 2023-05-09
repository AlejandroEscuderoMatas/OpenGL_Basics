#include "Shader.h"

Shader::Shader(std::string fileName) {
	this->fileName = fileName;

	if (fileName.ends_with(".vertex")) type = GL_VERTEX_SHADER;
	if (fileName.ends_with(".fragment")) type = GL_FRAGMENT_SHADER;

	idShader = glCreateShader(type);
	readSource();
	//compileShader();
}

void Shader::readSource()
{
	std::ifstream f(fileName);
	if (f.is_open())
	{
		//inicio del fichero y final del fichero
		source = std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
	}
	else
	{
		std::cout << "ERROR: FICHERO NO ENCONTRADO " << __FILE__ << ":" << __LINE__ << " " << fileName << "\n";
	}
}

void Shader::compileShader()
{
	const char* src = source.c_str();
	glShaderSource(idShader, 1, &src, nullptr);
	glCompileShader(idShader);

	//detección de errores de compliado
	checkErrors();
}

void Shader::checkErrors()
{
	GLint retCode;
	GLint fragment_compiled;

	glGetShaderiv(idShader, GL_COMPILE_STATUS, &fragment_compiled);

	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(idShader, 1024, &log_length, message);
		std::cout << "ERROR " << fileName << "\n" << message << "\n\n";
	}
}

void Shader::clean() {
	glDeleteShader(idShader);
}