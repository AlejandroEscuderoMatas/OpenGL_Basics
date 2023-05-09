#pragma once

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "vector4f.h"

using namespace std;

#define M_PI 3.1416f

#define TO_RADIANS(x) x*(M_PI/180.0f)
#define TO_DEGREES(x) x*(180.0f/M_PI)

typedef struct Matrix4x4f
{
	union {
		float matrix[4][4];
		float matrix1D[16];
		struct
		{
			Vector4f v1;
			Vector4f v2;
			Vector4f v3;
			Vector4f v4;
		};
	};
}Matrix4x4f;

class matrix4x4f
{
public:
	static Matrix4x4f make_identityf();
	static Matrix4x4f make_translate(float X, float Y, float Z);
	static Matrix4x4f make_rotate(float angleX, float angleY, float angleZ);
	static Matrix4x4f make_rotateQuat(float angle, float x, float y, float z);
	static Matrix4x4f make_rotateQuatMatrix(Vector4f v);
	static Matrix4x4f make_scale(float X, float Y, float Z);
	static Matrix4x4f matrixProduct(Matrix4x4f m1, Matrix4x4f m2);
	static Matrix4x4f escalarProduct(Matrix4x4f m, float n);
	static Vector4f vectorProduct(Matrix4x4f m, Vector4f v);
	static Matrix4x4f addition(Matrix4x4f m1, Matrix4x4f m2);
	static Matrix4x4f substraction(Matrix4x4f m1, Matrix4x4f m2);
	static Matrix4x4f transverse(Matrix4x4f m);
	static Matrix4x4f inverse_matrix(Matrix4x4f m);
};