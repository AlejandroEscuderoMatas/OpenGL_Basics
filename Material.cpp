#include "material.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Material::Material(std::string textureName, float ka, float kd, float ks)
{
	this->textureName = textureName;
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->textureUnitID = 0;

	int comp = 0;
	stbi_set_flip_vertically_on_load(true);
	//AQUI ESTAN TODOS LOS COLORES DESCOMPRIMIDOS
	unsigned char* data = (unsigned char*)stbi_load(this->textureName.c_str(), &this->width, &this->height, &comp, 4);
	if (data != nullptr)
	{
		//PEDIMOS RESERVAR MEMORIA A LA GPU CON EL IDENTIFICADOR, FUNCIONA COMO UNA REFERENCIA A LA MEMORIA PRINCIPAL
		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		//CONFIGURACION DE TEXTURA
		//FILTROS BILINEALES
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//REPETICION DE TEXTURA PARA LLENAR UN OBJETO, CON LA TEXTURA DE UN LADRILLO RELLENAMOS UNA PARED
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//COPIA UNA TEXTURA 2D USANDO LOS DATOS GUARDADOS EN DATA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//mat.enabled = 1;
	}
}

//DUDAS SOLO UN ID?
void Material::bind(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}