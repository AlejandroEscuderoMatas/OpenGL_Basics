#pragma once
#include "vertex.h"
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "vertex.h"
#include "Shader.h"
#include "Light.h"
#include "Material.h"

class Program
{
public:
	unsigned int idProgram = -1;
	std::vector<Shader*> shaderList;
	std::map<std::string, unsigned int> varList;

	Program();

	void addShader(std::string fileName);
	void linkProgram();
	void checkLinkerErrors();
	void readVarList();

	//Location es la posicion de arrais de atributos y de uniform que guarda las variables en GPU
	//Si no encuentra el atributo devuelve -1
	unsigned int getVarLocation(std::string varName);
	//unsigned int getPositionsLocations();
	//unsigned int getColorsLocations();
	//unsigned int getMVPLocations();

	void setAttribute(int location, void* description);
	void setUniformMatrix4x4(unsigned int location, float* matrix);

	void setVertexPositions(void* description);
	void setVertexColors(void* description);
	void setVertexNormals(void* description);
	void setVertexUVs(void* description);

	void setMatrixMVP(float* matrix);
	void setMatrixM(float* matrix);

	void setLight(Light light);
	void setMaterial(Material mat);

	void use();
	void clean();
};