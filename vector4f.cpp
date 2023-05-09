#include "vector4f.h"


float vector4f::lenght(Vector4f v)
{
	float lenght = sqrt(pow(v.data[0], 2) + pow(v.data[1], 2) + pow(v.data[2], 2));
	return lenght;
}

Vector4f vector4f::make_vector4f(float x, float y, float z, float w)
{
	Vector4f newVector;

	newVector.data[0] = x;
	newVector.data[1] = y;
	newVector.data[2] = z;

	//Siempre sera = 0 ya que los vectores siempre tienen w = 0
	newVector.data[3] = w;

	return newVector;
}

Vector4f vector4f::normalize(Vector4f v)
{
	float vectModule = sqrt(pow(v.data[0], 2) + pow(v.data[1], 2) + pow(v.data[2], 2));

	v = make_vector4f(v.data[0] / vectModule, v.data[1] / vectModule, v.data[2] / vectModule, 0);

	return v;
}

Vector4f vector4f::addition(Vector4f v1, Vector4f v2)
{
	Vector4f additionVector;

	additionVector = make_vector4f(v1.data[0] + v2.data[0], v1.data[1] + v2.data[1], v1.data[2] + v2.data[2], 0);

	return additionVector;
}

Vector4f vector4f::substraction(Vector4f v1, Vector4f v2)
{
	Vector4f subtractionVector;

	subtractionVector = make_vector4f(v1.data[0] - v2.data[0], v1.data[1] - v2.data[1], v1.data[2] - v2.data[2], 0);

	return subtractionVector;
}

Vector4f vector4f::escalarProduct(Vector4f v, float n)
{
	Vector4f productVector;

	productVector = make_vector4f(v.data[0] * n, v.data[1] * n, v.data[2] * n, 0);

	return productVector;
}

float vector4f::dotProduct(Vector4f v1, Vector4f v2)
{
	float dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	return dot;
}

Vector4f vector4f::vectorProduct(Vector4f v1, Vector4f v2)
{
	/*float productVector = 0;

	for(int i = 0; i < 3; i++)
	{
		productVector += v1.data[i]*v2.data[i];
	}

	return productVector;*/

	/*Vector4f crossed_vector;
	float i = (v1.data[1] * v2.data[2]) - (v1.data[2] * v2.data[1]);
	float j = (v1.data[0] * v2.data[2]) - (v1.data[2] * v2.data[0]);
	float k = (v1.data[0] * v2.data[1]) - (v1.data[1] * v2.data[0]);
	crossed_vector.data[0] = i;
	crossed_vector.data[1] = j;
	crossed_vector.data[2] = k;
	crossed_vector.data[3] = 0;
	return crossed_vector;*/

	Vector4f crossVector = make_vector4f((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x), 1.0f);
	return crossVector;
}




