#include "Camera.h"
#include "common.h"
#include "Render.h"
#include "OrbitalLight.h"
#include "Main.h"

int main(int argc, char** argv)
{
	Render render;

	Camera cam (vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f),
		vector4f::make_vector4f(0.0f, 0.0f, -3.0f, 1.0f),
		vector4f::make_vector4f(0.0f, 1.0f, 0.0f, 0.0f),
		vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 0.0f),
		90.0f, 0.01f, 100.0f, 4.0f / 3.0f);

	Vector4f lightPos1 = vector4f::make_vector4f(3.0f, 3.0f, 3.0f, 1.0f);
	Vector4f lightPos2 = vector4f::make_vector4f(0.0f, 3.0f, 3.0f, 1.0f);

	Light light1(lightPos1,
		vector4f::make_vector4f(1.0f, 1.0f, 1.0f, 1.0f),
		vector4f::normalize(vector4f::substraction(lightPos1, vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f))),
		lightTypes::directional,
		1.0f, 1.0f, 1.0f);

	Light light2 (lightPos2,
		vector4f::make_vector4f(0.0f, 1.0f, 0.0f, 1.0f),
		vector4f::normalize(vector4f::substraction(lightPos2, vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f))),
		lightTypes::puntual,
		1.0f, 1.0f, 1.0f);

	Object3D cube;

	render.putLights(&light1, &light2);
	render.initGL();
	
	cube.loadFromFile("data/cubeBlendTexture.vertc");
	render.setupObject(&cube);
	render.putCamera(&cam);
	
	render.mainLoop();

	return 0;
}