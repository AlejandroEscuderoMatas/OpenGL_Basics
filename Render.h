#pragma once


#define GLAD_ONLY_HEADERS
#include "common.h"
#include "object3D.h"
#include "Camera.h"
#include "InputManager.h"
#include "OrbitalLight.h"

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
	static inline std::vector<Object3D*> objectList;
	std::vector<Light*> lights;

	std::map<unsigned int, BufferObject> bufferList;
	
	void initGL();
	void setupObject(Object3D* obj);
	void putCamera(Camera* cam);
	void drawGL();
	void putLight(Light* light1);
	Light* getLight(unsigned int i);
	void mainLoop();
};
