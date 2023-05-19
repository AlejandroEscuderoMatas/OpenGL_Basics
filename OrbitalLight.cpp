#include "OrbitalLight.h"
#include "vector4f.h"


void OrbitalLight::move(double timeStep)
{
	float movePerFrame = 1 / 60;
	Matrix4x4f rotationMatrix = matrix4x4f::make_rotate(0.0f, movePerFrame*timeStep, 0.0f);
	//Matrix4x4f translationMatrix = matrix4x4f::make_translate(movePerFrame, 0.0f, 0.0f);

	this->position = vector4f::normalize(matrix4x4f::vectorProduct(rotationMatrix, position));
}
