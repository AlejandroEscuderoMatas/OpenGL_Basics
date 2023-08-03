#include "object3D.h"
#include "InputManager.h"


Object3D::Object3D()
{
	this->position = vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f);
	this->rotation = vector4f::make_vector4f(0.0f, 0.0f, 0.0f, 1.0f);
	this->scale    = vector4f::make_vector4f(1.0f, 1.0f, 1.0f, 1.0f);
	this->modelMatrix = matrix4x4f::make_identityf();

	this->id = counter;
	counter++;

	createObject();
}

void Object3D::loadFromFile(const char* fileName)
{
	std::ifstream f(fileName, std::ios_base::in);

	if (!f.is_open())
		std::cout << "ERROR, Fichero " << fileName << " no encontrado\n";
	else
	{
		idList.clear();
		vertexList.clear();

		int numFaces, numVertex;
		f >> numFaces >> numVertex;

		int id1, id2, id3;

		for (int i = 0; i < numFaces; i++)
		{
			f >> id1 >> id2 >> id3;

			idList.push_back(id1);
			idList.push_back(id2);
			idList.push_back(id3);
		}

		for (int i = 0; i < numVertex; i++)
		{
			Vertex v;
			f >> v.posicion.x >> v.posicion.y >> v.posicion.z >>
				v.color.r >> v.color.g >> v.color.b >> v.color.a >>
				v.normal.x >> v.normal.y >> v.normal.z >>
				v.uv.x >> v.uv.y;


			v.posicion.w = 1.0f;
			v.normal.w = 0.0f;

			vertexList.push_back(v);
		}

		//CARGA DEL SHADER
		std::string vshader, fshader, texture;

		f >> vshader;
		f >> fshader;
		prg = new Program();
		prg->addShader(vshader);
		prg->addShader(fshader);
		prg->linkProgram();
		f >> texture;
		//prg->clean();

		mat = new Material(texture, 0, 0, 0);

		this->coll = new Sphere();

		if (false)//mat.enabled) {
		{
			//añado píxeles "visibles"
			//buscar vértices máximos y mínimos
			Vector4f maximo = vector4f::make_vector4f(-9999.0f, -9999.0f, -9999.0f, 1.0f);
			Vector4f minimo = vector4f::make_vector4f(9999.0f, 9999.0f, 9999.0f, 1.0f);

			for (auto v : vertexList)
			{
				Vector4f particula = v.posicion;
				if (minimo.x > particula.x) minimo.x = particula.x;
				if (minimo.y > particula.y) minimo.y = particula.y;
				if (minimo.z > particula.z) minimo.z = particula.z;

				if (maximo.x < particula.x) maximo.x = particula.x;
				if (maximo.y < particula.y) maximo.y = particula.y;
				if (maximo.z < particula.z) maximo.z = particula.z;
			}
			float stepx = (maximo.x - minimo.x) / (float)mat->width;
			float stepy = (maximo.y - minimo.y) / (float)mat->height;

			for (int i = 0; i < mat->height; i++)
				for (int j = 0; j < mat->width; j++)
				{
					particle_t part = { 
						vector4f::make_vector4f(
							minimo.x + ((float)j + 1) * stepx,
							minimo.y + ((float)i + 1) * stepy,
							minimo.z, 1.0f
						),
						vector4f::make_vector4f(
							minimo.x + ((float)j) * stepx,
							minimo.y + ((float)i) * stepy,
							minimo.z, 1.0f
						) };
					if (mat->datargba[i * mat->width + j].a > 0)
						coll->addParticle(part);
				}
			coll->subdivide();
		}
		else
		{//añado vértices
			for (auto v : vertexList)
			{
				particle_t part{
					vector4f::make_vector4f(v.posicion.x + 0.1f,v.posicion.y + 0.1f,v.posicion.z + 0.1f,1.0f),

					vector4f::make_vector4f(v.posicion.x - 0.1f,v.posicion.y - 0.1f,v.posicion.z - 0.1f,1.0f)

				};
				coll->addParticle(part);
			}
			//coll->subdivide();

		}
		
	}
}
	

void Object3D::createObject()
{
	Vertex v1, v2, v3;
	v1.posicion = vector4f::make_vector4f(-0.5f, -0.5f, 0.0f, 1.0f);
	v2.posicion = vector4f::make_vector4f(0.0f, 0.5f, 0.0f, 1.0f);
	v3.posicion = vector4f::make_vector4f(0.5f, -0.5f, 0.0f, 1.0f);

	this->vertexList.push_back(v1);
	this->idList.push_back(0);

	this->vertexList.push_back(v2);
	this->idList.push_back(1);

	this->vertexList.push_back(v3);
	this->idList.push_back(2);
}

void Object3D::move(double timeStep)
{
	static float oldPosX = 0;
	static float oldPosY = 0;

	float speed = 0.01f;

	if(!InputManager::keysState[GLFW_KEY_LEFT_SHIFT])
	{
		if (InputManager::keysState[GLFW_KEY_A])
		{
			position.x += 0.001f * (float)timeStep;
		}
		if (InputManager::keysState[GLFW_KEY_D])
		{
			position.x -= 0.001f * (float)timeStep;
		}
		if (InputManager::keysState[GLFW_KEY_W])
		{
			position.y += 0.001f * (float)timeStep;
		}
		if (InputManager::keysState[GLFW_KEY_S])
		{
			position.y -= 0.001f * (float)timeStep;
		}
		if (InputManager::keysState[GLFW_KEY_UP])
		{
			scale.x += 0.001f * (float)timeStep;
			scale.y += 0.001f * (float)timeStep;
			scale.z += 0.001f * (float)timeStep;
		}
		if (InputManager::keysState[GLFW_KEY_DOWN])
		{
			scale.x -= 0.001f * (float)timeStep;
			scale.y -= 0.001f * (float)timeStep;
			scale.z -= 0.001f * (float)timeStep;
		}

		rotation.x += speed * (oldPosY - InputManager::posMY);
		rotation.y += speed * (oldPosX - InputManager::posMX);
	}

	oldPosX = InputManager::posMX;
	oldPosY = InputManager::posMY;

	//rotation.y += speed/10;
}

void Object3D::updateModelMatrix()
{
	Matrix4x4f translateMatrix = matrix4x4f::make_translate(position.x, position.y, position.z);
	Matrix4x4f rotateMatrix = matrix4x4f::make_rotate(rotation.x, (rotation.y), (rotation.z));
	Matrix4x4f scaleMatrix = matrix4x4f::make_scale(scale.x, scale.y, scale.z);

	modelMatrix = matrix4x4f::matrixProduct(matrix4x4f::matrixProduct(translateMatrix, rotateMatrix), scaleMatrix);
}

void Object3D::updateCollider()
{
	coll->update(modelMatrix);
}


