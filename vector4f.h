#pragma once

#include <iostream>
#include<math.h>
#include<stdlib.h>

using namespace std;

typedef struct Vector4f
{
	union {
		float data[4];
		struct {
			float x, y, z, w;
		};
		struct {
			float r, g, b, a;
		};
	};
}Vector4f;

class vector4f
{
public:
	static float lenght(Vector4f v);
	static Vector4f make_vector4f(float x, float y, float z,float w);
	static Vector4f normalize(Vector4f v);
	static Vector4f addition (Vector4f v1, Vector4f v2);
	static Vector4f substraction (Vector4f v1, Vector4f v2);
	static Vector4f escalarProduct (Vector4f v, float n);
	static float    dotProduct(Vector4f v1, Vector4f v2);
	static Vector4f vectorProduct(Vector4f v1, Vector4f v2);
};