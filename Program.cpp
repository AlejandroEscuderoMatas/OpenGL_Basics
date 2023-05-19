#include "Program.h"

Program::Program()
{
	//openGL asigna un id al programa
	idProgram = glCreateProgram();
}

void Program::addShader(std::string fileName)
{
	Shader* sh = new Shader(fileName);
	sh->compileShader();
	shaderList.push_back(sh);
}

void Program::linkProgram()
{
	glUseProgram(idProgram);
	for (auto i : shaderList)
		glAttachShader(idProgram, i->idShader);
	glLinkProgram(idProgram);

	//revisar errores
	checkLinkerErrors();
	readVarList();
}

void Program::checkLinkerErrors()
{
	GLint program_linked;

	glGetProgramiv(idProgram, GL_LINK_STATUS, &program_linked);

	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];

		glGetProgramInfoLog(idProgram, 1024, &log_length, message);
		std::cout << "ERROR \n" << message << "\n\n";

	}
}

void Program::readVarList()
{
	int numAttributes = 0;
	int numUniforms = 0;

	glGetProgramiv(idProgram, GL_ACTIVE_ATTRIBUTES, &numAttributes);
	for (int i = 0; i < numAttributes; i++) {
		char varName[100];
		int bufSize = 100, length = 0, size = 0;
		GLenum type = -1;
		glGetActiveAttrib(idProgram, (GLuint)i, bufSize, &length, &size, &type, varName);
		varList[std::string(varName)] = glGetAttribLocation(idProgram, varName);
	}

	glGetProgramiv(idProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
	for (int i = 0; i < numUniforms; i++) {
		char varName[100];
		int bufSize = 100, length = 0, size = 0;
		GLenum type = -1;
		glGetActiveUniform(idProgram, (GLuint)i, bufSize, &length, &size, &type, varName);
		varList[std::string(varName)] = glGetUniformLocation(idProgram, varName);
	}
}

//Location es la posicion de arrais de atributos y de uniform que guarda las variables en GPU
//Si no encuentra el atributo devuelve -1
unsigned int Program::getVarLocation(std::string varName) {
	if (varList.find(varName) != varList.end()) {
		return varList[varName];
	}
	else {
		std::cout << "ERROR: variable " << varName << " not found in shader!\n";
		return -1;
	}
}

void Program::setAttribute(int location, void* description)
{
	//Avismaos que vamos a utilizar estos datos
	glEnableVertexAttribArray(location);
	//Le describimos como estan ordenados esos datos
	glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), description);
}

void Program::setUniformMatrix4x4(unsigned int location, float* matrix)
{
	//Vamos a subir            una matriz que no esta transpuesta
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}

void Program::setVertexPositions(void* description)
{
	setAttribute(getVarLocation("pos"), description);
}

void Program::setVertexColors(void* description)
{
	setAttribute(getVarLocation("color"), description);
}

void Program::setVertexNormals(void* description) 
{
	setAttribute(getVarLocation("normal"), description);
}

void Program::setVertexUVs(void* description) {
	setAttribute(getVarLocation("uv"), description);
}

void Program::setMatrixMVP(float* matrix)
{
	setUniformMatrix4x4(getVarLocation("MVP"), matrix);
}

void Program::setMatrixM(float* matrix) 
{
	setUniformMatrix4x4(getVarLocation("M"), matrix);
}

void Program::setLight1(Light light)
{
	glUniform4fv(getVarLocation("light1.position"), 1, (float*)&(light.position.x));
	glUniform4fv(getVarLocation("light1.color"), 1, (float*)&(light.color.x));
	glUniform4fv(getVarLocation("light1.direction"), 1, (float*)&(light.direction.x));
	glUniform1i(getVarLocation("light1.type"), light.type);
	glUniform1f(getVarLocation("light1.ka"), light.ka);
	glUniform1f(getVarLocation("light1.kd"), light.kd);
	//glUniform1f(getVarLocation("light.ks"), light.ks);
}

void Program::setLight2(Light light)
{
	glUniform4fv(getVarLocation("light2.position"), 1, (float*)&(light.position.x));
	glUniform4fv(getVarLocation("light2.color"), 1, (float*)&(light.color.x));
	glUniform4fv(getVarLocation("light2.direction"), 1, (float*)&(light.direction.x));
	glUniform1i(getVarLocation("light2.type"), light.type);
	glUniform1f(getVarLocation("light2.ka"), light.ka);
	glUniform1f(getVarLocation("light2.kd"), light.kd);
	//glUniform1f(getVarLocation("light.ks"), light.ks);
}

void Program::setMaterial(Material mat)
{
	glUniform1i(getVarLocation("materials.textureUnitID"), mat.textureUnitID);
	//glUniform1i(getVarLocation("materials.enabled"), mat.enabled);
}

void Program::use()
{
	//AHORA DECIMOS NOSOTROS COMO PINTA LA GPU, no OpenGl
	glUseProgram(idProgram);
}

void Program::clean()
{
	for (auto i : shaderList)
		i->clean();
	glDeleteProgram(idProgram);
}