#pragma once


#define GLAD_ONLY_HEADERS
#include "common.h"
#include "object3D.h"
#include "Camera.h"
#include "InputManager.h"

typedef struct
{
	unsigned int bufferId;
	unsigned int vertId;
	unsigned int listId;
}BufferObject;

class Render
{
public:
	GLFWwindow* window;
	Camera* camera;
	Matrix4x4f proyectionMatrixAux;
	std::vector<Object3D*> objectList;
	Light* light;

	std::map<unsigned int, BufferObject> bufferList;
	
	void initGL();
	void setupObject(Object3D* obj);
	void putCamera(Camera* cam);
	void drawGL();
	void putLight(Light* light);
	Light* getLight();
	void mainLoop();
};
