#include "Matrix4x4f.h"
#include <cmath>

Matrix4x4f matrix4x4f::make_identityf()
{
	Matrix4x4f newMatrix;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(i == j)
				newMatrix.matrix[i][j] = 1;
			else
				newMatrix.matrix[i][j] = 0;
		}
	}

	return newMatrix;
}

Matrix4x4f matrix4x4f::make_translate(float X, float Y, float Z)
{
	Matrix4x4f translationMatrix = make_identityf();
	float translation[3] = {X, Y, Z};

	for(int i = 0; i < 3; i++)
	{
		translationMatrix.matrix[i][3] = translation[i];
	}

	return translationMatrix;
}

Matrix4x4f matrix4x4f::make_rotate(float angleX, float angleY, float angleZ)
{
	Matrix4x4f rotationMatrix  = make_identityf();

	Matrix4x4f rotationMatrixX = make_identityf();
	Matrix4x4f rotationMatrixY = make_identityf();
	Matrix4x4f rotationMatrixZ = make_identityf();

	//Matriz de rotacion del eje x
	rotationMatrixX.matrix[1][1] =  cos(angleX);
	rotationMatrixX.matrix[1][2] = -sin(angleX);
	rotationMatrixX.matrix[2][1] =  sin(angleX);
	rotationMatrixX.matrix[2][2] =  cos(angleX);

	//Matriz de rotacion del eje y
	rotationMatrixY.matrix[0][0] =  cos(angleY);
	rotationMatrixY.matrix[0][2] =  sin(angleY);
	rotationMatrixY.matrix[2][0] = -sin(angleY);
	rotationMatrixY.matrix[2][2] =  cos(angleY);

	//Matriz de rotacion del eje z
	rotationMatrixZ.matrix[0][0] =  cos(angleZ);
	rotationMatrixZ.matrix[0][1] = -sin(angleZ);
	rotationMatrixZ.matrix[1][0] =  sin(angleZ);
	rotationMatrixZ.matrix[1][1] =  cos(angleZ);

	rotationMatrix = matrixProduct(matrixProduct(rotationMatrixX, rotationMatrixY), rotationMatrixZ);

	return rotationMatrix;
}

Matrix4x4f matrix4x4f::make_rotateQuat(float angle, float x, float y, float z)
{
	Vector4f normalVector = vector4f::make_vector4f(x, y, z, 1);
	normalVector = vector4f::normalize(normalVector);

	//tuple = w, x, y, z
	float tuple[4] = { cos(angle)
					 , normalVector.data[0] * sin(angle * 0.5f)
					 , normalVector.data[1] * sin(angle * 0.5f)
					 , normalVector.data[2] * sin(angle * 0.5f)};

	Vector4f quatVector = vector4f::make_vector4f(tuple[1], tuple[2], tuple[3], tuple[0]);

	return make_rotateQuatMatrix(quatVector);
}

Matrix4x4f matrix4x4f::make_rotateQuatMatrix(Vector4f v)
{
	Matrix4x4f rotationQuatMatrix = make_identityf();

	rotationQuatMatrix.matrix[0][0] = (1 - 2 * v.data[1] * v.data[1] - 2 * v.data[2] * v.data[2]);
	rotationQuatMatrix.matrix[0][1] = (2 * v.data[0] * v.data[1] - 2 * v.data[3] * v.data[2]);
	rotationQuatMatrix.matrix[0][2] = (2 * v.data[0] * v.data[2] + 2 * v.data[3] * v.data[1]);

	rotationQuatMatrix.matrix[1][0] = (2 * v.data[0] * v.data[1] + 2 * v.data[3] * v.data[2]);
	rotationQuatMatrix.matrix[1][1] = (1 - 2 * v.data[0] * v.data[0] - 2 * v.data[2] * v.data[2]);
	rotationQuatMatrix.matrix[1][2] = (2 * v.data[1] * v.data[2] - 2 * v.data[3] * v.data[0]);

	rotationQuatMatrix.matrix[0][0] = (2 * v.data[0] * v.data[2] - 2 * v.data[3] * v.data[1]);
	rotationQuatMatrix.matrix[0][1] = (2 * v.data[1] * v.data[2] + 2 * v.data[3] * v.data[0]);
	rotationQuatMatrix.matrix[0][2] = (1 - 2 * v.data[0] * v.data[0] - 2 * v.data[1] * v.data[1]);

	return rotationQuatMatrix;
}

Matrix4x4f matrix4x4f::escalarProduct(Matrix4x4f m, float n)
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			m.matrix[i][j] *= n;
		}
	}

	return m;
}


Matrix4x4f matrix4x4f::make_scale(float X, float Y, float Z)
{
	Matrix4x4f scaleMatrix = make_identityf();
	const float scale[3] = {X, Y, Z};

	for(int i = 0; i < 3; i++)
	{
		scaleMatrix.matrix[i][i] = scale[i];
	}

	return scaleMatrix;
}

Matrix4x4f matrix4x4f::matrixProduct(Matrix4x4f m1, Matrix4x4f m2)
{
	Matrix4x4f productMatrix = make_identityf();
	float producto = 0;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			for(int k = 0; k < 4; k++)
			{
				producto += (m1.matrix[i][k] * m2.matrix[k][j]);
			}
			productMatrix.matrix[i][j] = producto;
			producto = 0;
		}
	}

	return productMatrix;
}

Vector4f matrix4x4f::vectorProduct(Matrix4x4f m, Vector4f v)
{
	//DEVOLVERA UNA MATRIZ 4X1, ES DECIR UN VECTOR
	Vector4f productVector;
	float sumaProductos = 0;

	for (int i = 0; i < 4; i++)
	{
		sumaProductos = 0;
		for (int k = 0; k < 4; k++)
		{
			sumaProductos += m.matrix[i][k] * v.data[k];
		}
		productVector.data[i] = sumaProductos;
		
	}

	return productVector;
}

Matrix4x4f matrix4x4f::addition(Matrix4x4f m1, Matrix4x4f m2)
{
	Matrix4x4f additionMatrix = make_identityf();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			additionMatrix.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
		}
	}

	return additionMatrix;
}

Matrix4x4f matrix4x4f::substraction(Matrix4x4f m1, Matrix4x4f m2)
{
	Matrix4x4f substractionMatrix = make_identityf();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			substractionMatrix.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
		}
	}

	return substractionMatrix;
}

Matrix4x4f matrix4x4f::transverse(Matrix4x4f m)
{
	Matrix4x4f transverseMatrix = make_identityf();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			transverseMatrix.matrix[i][j] = m.matrix[j][i];
		}
	}

	return transverseMatrix;
}

Matrix4x4f matrix4x4f::inverse_matrix(Matrix4x4f m)
{
	Matrix4x4f invOut = { 1 };
	Matrix4x4f inv = { 0 };
	float det;
	int i;

	inv.matrix1D[0] = m.matrix1D[5] * m.matrix1D[10] * m.matrix1D[15] -
		m.matrix1D[5] * m.matrix1D[11] * m.matrix1D[14] -
		m.matrix1D[9] * m.matrix1D[6] * m.matrix1D[15] +
		m.matrix1D[9] * m.matrix1D[7] * m.matrix1D[14] +
		m.matrix1D[13] * m.matrix1D[6] * m.matrix1D[11] -
		m.matrix1D[13] * m.matrix1D[7] * m.matrix1D[10];

	inv.matrix1D[4] = -m.matrix1D[4] * m.matrix1D[10] * m.matrix1D[15] +
		m.matrix1D[4] * m.matrix1D[11] * m.matrix1D[14] +
		m.matrix1D[8] * m.matrix1D[6] * m.matrix1D[15] -
		m.matrix1D[8] * m.matrix1D[7] * m.matrix1D[14] -
		m.matrix1D[12] * m.matrix1D[6] * m.matrix1D[11] +
		m.matrix1D[12] * m.matrix1D[7] * m.matrix1D[10];

	inv.matrix1D[8] = m.matrix1D[4] * m.matrix1D[9] * m.matrix1D[15] -
		m.matrix1D[4] * m.matrix1D[11] * m.matrix1D[13] -
		m.matrix1D[8] * m.matrix1D[5] * m.matrix1D[15] +
		m.matrix1D[8] * m.matrix1D[7] * m.matrix1D[13] +
		m.matrix1D[12] * m.matrix1D[5] * m.matrix1D[11] -
		m.matrix1D[12] * m.matrix1D[7] * m.matrix1D[9];

	inv.matrix1D[12] = -m.matrix1D[4] * m.matrix1D[9] * m.matrix1D[14] +
		m.matrix1D[4] * m.matrix1D[10] * m.matrix1D[13] +
		m.matrix1D[8] * m.matrix1D[5] * m.matrix1D[14] -
		m.matrix1D[8] * m.matrix1D[6] * m.matrix1D[13] -
		m.matrix1D[12] * m.matrix1D[5] * m.matrix1D[10] +
		m.matrix1D[12] * m.matrix1D[6] * m.matrix1D[9];

	inv.matrix1D[1] = -m.matrix1D[1] * m.matrix1D[10] * m.matrix1D[15] +
		m.matrix1D[1] * m.matrix1D[11] * m.matrix1D[14] +
		m.matrix1D[9] * m.matrix1D[2] * m.matrix1D[15] -
		m.matrix1D[9] * m.matrix1D[3] * m.matrix1D[14] -
		m.matrix1D[13] * m.matrix1D[2] * m.matrix1D[11] +
		m.matrix1D[13] * m.matrix1D[3] * m.matrix1D[10];

	inv.matrix1D[5] = m.matrix1D[0] * m.matrix1D[10] * m.matrix1D[15] -
		m.matrix1D[0] * m.matrix1D[11] * m.matrix1D[14] -
		m.matrix1D[8] * m.matrix1D[2] * m.matrix1D[15] +
		m.matrix1D[8] * m.matrix1D[3] * m.matrix1D[14] +
		m.matrix1D[12] * m.matrix1D[2] * m.matrix1D[11] -
		m.matrix1D[12] * m.matrix1D[3] * m.matrix1D[10];

	inv.matrix1D[9] = -m.matrix1D[0] * m.matrix1D[9] * m.matrix1D[15] +
		m.matrix1D[0] * m.matrix1D[11] * m.matrix1D[13] +
		m.matrix1D[8] * m.matrix1D[1] * m.matrix1D[15] -
		m.matrix1D[8] * m.matrix1D[3] * m.matrix1D[13] -
		m.matrix1D[12] * m.matrix1D[1] * m.matrix1D[11] +
		m.matrix1D[12] * m.matrix1D[3] * m.matrix1D[9];

	inv.matrix1D[13] = m.matrix1D[0] * m.matrix1D[9] * m.matrix1D[14] -
		m.matrix1D[0] * m.matrix1D[10] * m.matrix1D[13] -
		m.matrix1D[8] * m.matrix1D[1] * m.matrix1D[14] +
		m.matrix1D[8] * m.matrix1D[2] * m.matrix1D[13] +
		m.matrix1D[12] * m.matrix1D[1] * m.matrix1D[10] -
		m.matrix1D[12] * m.matrix1D[2] * m.matrix1D[9];

	inv.matrix1D[2] = m.matrix1D[1] * m.matrix1D[6] * m.matrix1D[15] -
		m.matrix1D[1] * m.matrix1D[7] * m.matrix1D[14] -
		m.matrix1D[5] * m.matrix1D[2] * m.matrix1D[15] +
		m.matrix1D[5] * m.matrix1D[3] * m.matrix1D[14] +
		m.matrix1D[13] * m.matrix1D[2] * m.matrix1D[7] -
		m.matrix1D[13] * m.matrix1D[3] * m.matrix1D[6];

	inv.matrix1D[6] = -m.matrix1D[0] * m.matrix1D[6] * m.matrix1D[15] +
		m.matrix1D[0] * m.matrix1D[7] * m.matrix1D[14] +
		m.matrix1D[4] * m.matrix1D[2] * m.matrix1D[15] -
		m.matrix1D[4] * m.matrix1D[3] * m.matrix1D[14] -
		m.matrix1D[12] * m.matrix1D[2] * m.matrix1D[7] +
		m.matrix1D[12] * m.matrix1D[3] * m.matrix1D[6];

	inv.matrix1D[10] = m.matrix1D[0] * m.matrix1D[5] * m.matrix1D[15] -
		m.matrix1D[0] * m.matrix1D[7] * m.matrix1D[13] -
		m.matrix1D[4] * m.matrix1D[1] * m.matrix1D[15] +
		m.matrix1D[4] * m.matrix1D[3] * m.matrix1D[13] +
		m.matrix1D[12] * m.matrix1D[1] * m.matrix1D[7] -
		m.matrix1D[12] * m.matrix1D[3] * m.matrix1D[5];

	inv.matrix1D[14] = -m.matrix1D[0] * m.matrix1D[5] * m.matrix1D[14] +
		m.matrix1D[0] * m.matrix1D[6] * m.matrix1D[13] +
		m.matrix1D[4] * m.matrix1D[1] * m.matrix1D[14] -
		m.matrix1D[4] * m.matrix1D[2] * m.matrix1D[13] -
		m.matrix1D[12] * m.matrix1D[1] * m.matrix1D[6] +
		m.matrix1D[12] * m.matrix1D[2] * m.matrix1D[5];

	inv.matrix1D[3] = -m.matrix1D[1] * m.matrix1D[6] * m.matrix1D[11] +
		m.matrix1D[1] * m.matrix1D[7] * m.matrix1D[10] +
		m.matrix1D[5] * m.matrix1D[2] * m.matrix1D[11] -
		m.matrix1D[5] * m.matrix1D[3] * m.matrix1D[10] -
		m.matrix1D[9] * m.matrix1D[2] * m.matrix1D[7] +
		m.matrix1D[9] * m.matrix1D[3] * m.matrix1D[6];

	inv.matrix1D[7] = m.matrix1D[0] * m.matrix1D[6] * m.matrix1D[11] -
		m.matrix1D[0] * m.matrix1D[7] * m.matrix1D[10] -
		m.matrix1D[4] * m.matrix1D[2] * m.matrix1D[11] +
		m.matrix1D[4] * m.matrix1D[3] * m.matrix1D[10] +
		m.matrix1D[8] * m.matrix1D[2] * m.matrix1D[7] -
		m.matrix1D[8] * m.matrix1D[3] * m.matrix1D[6];

	inv.matrix1D[11] = -m.matrix1D[0] * m.matrix1D[5] * m.matrix1D[11] +
		m.matrix1D[0] * m.matrix1D[7] * m.matrix1D[9] +
		m.matrix1D[4] * m.matrix1D[1] * m.matrix1D[11] -
		m.matrix1D[4] * m.matrix1D[3] * m.matrix1D[9] -
		m.matrix1D[8] * m.matrix1D[1] * m.matrix1D[7] +
		m.matrix1D[8] * m.matrix1D[3] * m.matrix1D[5];

	inv.matrix1D[15] = m.matrix1D[0] * m.matrix1D[5] * m.matrix1D[10] -
		m.matrix1D[0] * m.matrix1D[6] * m.matrix1D[9] -
		m.matrix1D[4] * m.matrix1D[1] * m.matrix1D[10] +
		m.matrix1D[4] * m.matrix1D[2] * m.matrix1D[9] +
		m.matrix1D[8] * m.matrix1D[1] * m.matrix1D[6] -
		m.matrix1D[8] * m.matrix1D[2] * m.matrix1D[5];

	det = m.matrix1D[0] * inv.matrix1D[0] + m.matrix1D[1] * inv.matrix1D[4] + m.matrix1D[2] * inv.matrix1D[8] + m.matrix1D[3] * inv.matrix1D[12];

	if (det == 0)
		std::cout << "det is zero" << std::endl;
	else {
		det = 1.0 / det;

		for (i = 0; i < 16; i++)
			invOut.matrix1D[i] = inv.matrix1D[i] * det;
	}

	return invOut;
}
