#pragma once

#include "Light.h"
#include "matrix4x4f.h"

class OrbitalLight : public Light
{
public:
	virtual void move(double timeStep) override;
};

