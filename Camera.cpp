#include "Camera.h"

#include "InputManager.h"

Camera::Camera(Vector4f lookAt, Vector4f pos, Vector4f rot, Vector4f Up, float fovy, float zNear, float zFar, float aspectRatio)
{
	this->pos         = pos;
	this->rot         = rot;
	this->lookAt      = lookAt;
	this->Up          = Up;
	this->fovy        = fovy;
	this->dir         = vector4f::substraction(lookAt, pos);
	this->aspectRatio = aspectRatio;
	this->zNear       = zNear;
	this->zFar        = zFar;
	this->radious     = vector4f::substraction(lookAt, pos);
	this->rotXY       = vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f);

	perspective();
}

Matrix4x4f Camera::view()
{
	Matrix4x4f m = matrix4x4f::make_identityf();
	Vector4f up, forward, right;
	forward = vector4f::normalize(vector4f::substraction(lookAt, pos));
	forward.w = 0;
	right = vector4f::normalize(vector4f::vectorProduct(forward, rot));
	right.w = 0;
	up = vector4f::vectorProduct(right, forward);
	up.w = 0;

	m.matrix[0][0] = right.x;
	m.matrix[1][0] = right.y;
	m.matrix[2][0] = right.z;
	m.matrix[0][1] = up.x;
	m.matrix[1][1] = up.y;
	m.matrix[2][1] = up.z;
	m.matrix[0][2] = -forward.x;
	m.matrix[1][2] = -forward.y;
	m.matrix[2][2] = -forward.z;
	m.matrix[3][0] = -vector4f::dotProduct(right, pos);
	m.matrix[3][1] = -vector4f::dotProduct(up, pos);
	m.matrix[3][2] = vector4f::dotProduct(forward, pos);

	return matrix4x4f::transverse(m);
}

Matrix4x4f Camera::perspective()
{
	Matrix4x4f m;// = make_identityf();
	memset(&m, 0, sizeof(float) * 16);
	float tangent = (float)tan(TO_RADIANS(fovy) * 0.5f);

	m.matrix[0][0] = 1.0f / (aspectRatio * tangent);
	m.matrix[1][1] = 1.0f / (tangent);
	m.matrix[2][2] = -(zFar + zNear) / (zFar - zNear);
	m.matrix[2][3] = -2.0f * zFar * zNear / (zFar - zNear);
	m.matrix[3][2] = -1.0f;
	//m.matrix[3][3] = 1.0f;

	return m;
}

void Camera::Move(double timeStep)
{
	static float prevMX = 0, prevMY = 0;

	if (InputManager::keysState[GLFW_KEY_LEFT_SHIFT])
	{
		//MOVIMIENTOS PLANO HORIZONTAL
		if (InputManager::keysState[GLFW_KEY_D])
		{
			this->pos.x += 0.001f;
		}
		if (InputManager::keysState[GLFW_KEY_A])
		{
			this->pos.x -= 0.001f;
		}
		//PARA ACERCARNOS Y ALEJARNOS LO INVERTIMOS, YA QUE LA CAMARA MIRA HACIA EL EJE Z NEGATIVO
		if (InputManager::keysState[GLFW_KEY_W])
		{
			//this->pos.z += 0.001f;
			this->pos = vector4f::addition(this->pos, vector4f::escalarProduct(this->dir, 0.001f));
			this->dir = vector4f::substraction(lookAt, pos);
		}
		if (InputManager::keysState[GLFW_KEY_S])
		{
			//this->pos.z -= 0.001f;
			this->pos = vector4f::substraction(this->pos, vector4f::escalarProduct(this->dir, 0.001f));
			this->dir = vector4f::substraction(lookAt, pos);
		}
		/*if(InputManager::keysState[GLFW_KEY_UP])
		{
			this->Up.x += 0.001f;
		}*/

		//MOVIMIENTOS DE ROTACION
		float speedX = InputManager::posMX - prevMX;
		float speedY = InputManager::posMY - prevMY;

		this->rotXY.x -= speedY * 0.01;
		this->rotXY.y += speedX * 0.01;
		Matrix4x4f mRot = matrix4x4f::make_rotate(this->rotXY.x, this->rotXY.y, 0.0f);

		//ROTAMOS Y LUEGO TRASLADAMOS
		this->lookAt = matrix4x4f::vectorProduct(mRot, this->radious);
		this->lookAt = vector4f::addition(this->lookAt, this->pos);
	}

	prevMX = InputManager::posMX;
	prevMY = InputManager::posMY;
}