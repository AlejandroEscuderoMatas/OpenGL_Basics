#include "Camera.h"
#include "common.h"
#include "Render.h"

int main(int argc, char** argv)
{
	Render render;

	Camera cam (vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f),
		vector4f::make_vector4f(0.0f, 0.0f, -3.0f, 1.0f),
		vector4f::make_vector4f(0.0f, 1.0f, 0.0f, 0.0f),
		vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 0.0f),
		90.0f, 0.01f, 100.0f, 4.0f / 3.0f);

	Vector4f lightPos = vector4f::make_vector4f(3.0f, 3.0f, 3.0f, 1.0f);

	Light light(lightPos,
		vector4f::make_vector4f(1.0f, 1.0f, 1.0f, 1.0f),
		vector4f::normalize(vector4f::substraction(lightPos, vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f))),
		lightTypes::directional,
		1.0f, 1.0f, 1.0f);

	Object3D cube;

	render.putLight(&light);
	render.initGL();
	
	cube.loadFromFile("data/cubeBlendTexture.vertc");
	render.setupObject(&cube);
	render.putCamera(&cam);
	
	render.mainLoop();

	return 0;
}