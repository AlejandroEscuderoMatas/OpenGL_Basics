#pragma once
#include "object3D.h"
#include "vector4f.h"

class collider
{
public:
	typedef enum {sphere, AABB} collTypes;
	collTypes type;

	std::vector<Vector4f> partList;

	collider() {}
	virtual void addParticle(Vector4f particle) = 0;
	virtual bool test(collider* c2) = 0;
};

class sphere: public collider
{
public:
	Vector4f center = vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f);
	float radious = 0;

	Vector4f minCoord = vector4f::make_vector4f(9999.0f, 9999.0f, 9999.0f, 1.0f);
	Vector4f maxCoord = vector4f::make_vector4f(-9999.0f, 9999.0f, 9999.0f, 1.0f);

	void addParticle(Vector4f particle) override
	{
		partList.push_back(particle);

		if (minCoord.x > particle.x) minCoord.x = particle.x;
		if (minCoord.y > particle.y) minCoord.y = particle.y;
		if (minCoord.z > particle.z) minCoord.z = particle.z;

		if (maxCoord.x > particle.x) maxCoord.x = particle.x;
		if (maxCoord.y > particle.y) maxCoord.y = particle.y;
		if (maxCoord.z > particle.z) maxCoord.z = particle.z;

		center = vector4f::escalarProduct(vector4f::substraction(maxCoord, minCoord), 0.5);
		radious = vector4f::lenght(vector4f::substraction(maxCoord, minCoord)) / 2.0f;
	}

	bool test(collider* c2) override
	{
		if (c2->type != collTypes::sphere)
			return false;

		sphere* s2 = (sphere*)c2;
		return vector4f::lenght(vector4f::substraction(this->center, s2->center)) < (this->radious + s2->radious);
	}

	sphere()
	{
		this->type = collTypes::sphere;
	}

	~sphere() {}
};

