#include "OrbitalLight.h"
#include "vector4f.h"

OrbitalLight::OrbitalLight(Vector4f position, Vector4f color, Vector4f direction, int  type, float ka, float kd, float ks)
{
	this->position = position;
	this->color = color;
	this->direction = direction;
	this->type = type;
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
}

