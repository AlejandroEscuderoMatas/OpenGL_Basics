#pragma once

#include "matrix4x4f.h"
#include "vertex.h"

class Camera
{
public:
	Vector4f pos;
	Vector4f rot;
	Vector4f lookAt;
	Vector4f Up;

	//MOVER EL VECTOR DIR Y DEJAR EL RADIOUS FIJO
	Vector4f dir;

	float fovy;
	float aspectRatio;
	float zNear;
	float zFar;

	//radius
	Vector4f radious;
	Vector4f rotXY;

	Camera(Vector4f lookAt, Vector4f pos, Vector4f rot, Vector4f Up, float fovy, float zNear, float zFar, float aspectRatio);
	Matrix4x4f view();
	Matrix4x4f perspective();
	void Move(double timeStep);
};