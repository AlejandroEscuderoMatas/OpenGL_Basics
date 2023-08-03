#pragma once

#include "Light.h"
#include "matrix4x4f.h"

class OrbitalLight : public Light
{
public:
	OrbitalLight() {}
	OrbitalLight(Vector4f position, Vector4f color, Vector4f direction, int  type, float ka, float kd, float ks);

	void move(double timeStep) override {
		static Vector4f positionCenter = {0.0f, 0.0f, 3.0f, 1.0f};
		static float angle = 0;
		float movePerFrame = (3.14 * 2.0f) / (32 * 120.0f);
		angle += movePerFrame;

		if (angle == 3.14f * 2) angle = 0;

		Matrix4x4f rotationMatrix = matrix4x4f::make_rotate(0.0f, angle, 0.0f);

		//std::cout << position.x << "::::" << position.y << "::::" << position.z << "\n";

		this->position = matrix4x4f::vectorProduct(rotationMatrix, positionCenter);
	}

};

