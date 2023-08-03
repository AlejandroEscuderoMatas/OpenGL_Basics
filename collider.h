#pragma once
#include "vector4f.h"

typedef struct particle_t {
	Vector4f max, min;
}particle_t;

class Collider
{
public:
	typedef enum { sphere, AABB }collTypes;
	collTypes type;

	Collider() {};
	std::vector< particle_t> partList;
	std::vector<Collider*> sons;

	virtual void addParticle(particle_t part) = 0;
	virtual bool test(Collider* c2) = 0;
	virtual void update(Matrix4x4f mat) = 0;
	virtual void subdivide() = 0;
};

class Sphere: public Collider
{
public:
	Vector4f center = vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f);
	float radious = 0;

	Vector4f minCoord = vector4f::make_vector4f(9999.0f, 9999.0f, 9999.0f, 1.0f);
	Vector4f maxCoord = vector4f::make_vector4f(-9999.0f, -9999.0f, -9999.0f, 1.0f);

	Sphere()
	{
		this->type = collTypes::sphere;
	}

	void addParticle(particle_t particle) override {
		partList.push_back(particle);

		if (minCoord.x > particle.min.x) minCoord.x = particle.min.x;
		if (minCoord.y > particle.min.y) minCoord.y = particle.min.y;
		if (minCoord.z > particle.min.z) minCoord.z = particle.min.z;

		if (maxCoord.x < particle.max.x) maxCoord.x = particle.max.x;
		if (maxCoord.y < particle.max.y) maxCoord.y = particle.max.y;
		if (maxCoord.z < particle.max.z) maxCoord.z = particle.max.z;

		center = vector4f::escalarProduct(vector4f::addition(maxCoord, minCoord), 0.5);
		radious = vector4f::lenght(vector4f::substraction(maxCoord, minCoord)) / 2.0f;
	}

	bool test(Collider* c2) override {
		if (c2->type != collTypes::sphere)
			return false;
		Sphere* s2 = (Sphere*)c2;

		if (vector4f::lenght(vector4f::substraction(this->center, s2->center)) < (this->radious + s2->radious)) {
			//ambos son hojas
			if (this->sons.size() == 0 && s2->sons.size() == 0)
			{
				return true;// (libMath::length(this->center - s2->center) < (this->radious + s2->radious));
			}
			else //una hoja y una rama
			{
				if (this->sons.size() > 0 && s2->sons.size() == 0)
				{
					bool res = false;
					for (auto& c : this->sons)
					{
						res |= c->test(s2);
					}
					return res;
				}
				else if (s2->sons.size() > 0 && this->sons.size() == 0)
				{
					bool res = false;
					for (auto& c : s2->sons)
					{
						res |= c->test(this);
					}
					return res;
				}
				else if (s2->sons.size() > 0 && this->sons.size() > 0) {//ambos ramas
					bool res = false;
					for (auto& c : this->sons)
					{
						for (auto& c2 : s2->sons)
						{
							res |= c->test(c2);
						}
					}
					return res;
				}
			}
		}
		else {
			return false;
		}
	}

	void update(Matrix4x4f mat) override
	{
		Vector4f max = matrix4x4f::vectorProduct(mat, maxCoord);
		Vector4f min = matrix4x4f::vectorProduct(mat, minCoord);

		center = vector4f::escalarProduct(vector4f::addition(maxCoord, minCoord), 0.5);
		radious = vector4f::lenght(vector4f::substraction(maxCoord, minCoord)) / 2.0f;

		for (auto& c : sons)
		{
			c->update(mat);
		}
	}
	
	void subdivide()
	{
		if (partList.size() == 1) return;

		Sphere* SI = new Sphere();
		Sphere* SD = new Sphere();
		Sphere* II = new Sphere();
		Sphere* ID = new Sphere();

		for (auto& p : partList)
		{
			Vector4f pcenter = vector4f::escalarProduct(vector4f::addition(maxCoord, minCoord), 0.5);
			//izquierda de centro
			if (pcenter.x < center.x)
			{
				//superior centro
				if (pcenter.y > center.y)
					SI->addParticle(p);
				else II->addParticle(p);
			}
			else {
				//superior centro
				if (pcenter.y > center.y)
					SD->addParticle(p);
				else
					ID->addParticle(p);
			}
		}

		if (SI->partList.size() > 0) {
			sons.push_back(SI);
			if (SI->partList.size() > 1) SI->subdivide();
		}
		if (SD->partList.size() > 0) {
			sons.push_back(SD);
			if (SD->partList.size() > 1)
				SD->subdivide();
		}
		if (II->partList.size() > 0) {
			sons.push_back(II);
			if (II->partList.size() > 1)
				II->subdivide();
		}
		if (ID->partList.size() > 0) {
			sons.push_back(ID);
			if (ID->partList.size() > 1)
				ID->subdivide();
		}
	}

	~Sphere() {}
};

