#pragma once

#define GLAD_ONLY_HEADERS
#include "common.h"
#include <vector>
#include "vector4f.h"
#include "matrix4x4f.h"
#include "vertex.h"
#include "Program.h"
#include "collider.h"


class Object3D
{
public:
	unsigned int id;
	static inline unsigned int counter = 0;

	Vector4f position;
	Vector4f rotation;
	Vector4f scale;
	Matrix4x4f modelMatrix;
	Program* prg;
	Material* mat;

	Sphere* coll;

	std::vector<Vertex> vertexList;
	std::vector<int>    idList;

	Object3D();
	void loadFromFile(const char* fileName);
	void createObject();
	void move(double timeStep);
	void updateModelMatrix();
	void updateCollider();
};