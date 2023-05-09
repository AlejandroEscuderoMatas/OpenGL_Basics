#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "matrix4x4f.h"

typedef enum {
	directional = 0, puntual = 1
}lightTypes;

class Light
{
public:
	Vector4f position;
	Vector4f color;
	Vector4f direction;
	lightTypes  type;

	float ka;
	float kd;
	float ks;

	Light(Vector4f position, Vector4f color, Vector4f direction, lightTypes  type, float ka, float kd, float ks);

	void move(double timeStep);
};