#pragma once

#define GLAD_ONLY_HEADERS
#include "common.h"
#include "matrix4x4f.h"

class Material
{
public:
	std::string textureName;
	unsigned int textureID;
	unsigned int textureUnitID;
	int width, height;
	float ka, kd, ks;

	Material(std::string textureName, float ka, float kd, float ks);
	void bind(int textureUnit);
};