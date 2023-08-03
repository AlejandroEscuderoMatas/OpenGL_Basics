#include "Light.h"
#include "InputManager.h"

Light::Light(Vector4f position,
	Vector4f color,
	Vector4f direction,
	int  type,
	float ka,
	float kd,
	float ks)
{
	this->color     = color;
	this->direction = direction;
	this->type      = type;
	this->ka        = ka;
	this->kd        = kd;
	this->ks        = ks;
}

void Light::move(double timeStep)
{
}