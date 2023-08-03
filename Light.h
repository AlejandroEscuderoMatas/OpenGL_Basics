#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "matrix4x4f.h"

#define DIRECTIONAL 0
#define PUNTUAL 1

/*typedef enum {
	directional = 0, puntual = 1
}lightTypes;
*/
class Light
{
public:
	Vector4f position;
	Vector4f color;
	Vector4f direction;
	int  type;

	float ka;
	float kd;
	float ks;

	Light() {};
	Light(Vector4f position, Vector4f color, Vector4f direction, int  type, float ka, float kd, float ks);

	virtual void move(double timeStep);
};