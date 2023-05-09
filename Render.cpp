#include "Render.h"

void Render::initGL()
{
	if (!glfwInit())
		std::cout << "ERROR: GLFWINIT\n";
	else
		std::cout << "GLFW Iniciado\n";

#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

	//Inicializaciones
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(640, 480, "Hello Triangle", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPos(window, 0.0, 0.0);

	//DESPUES DE ESTO PODEMOS EMPEZAR A DIBUJAR
	gladLoadGL(glfwGetProcAddress);

	//ACTIVAR LA PROFUNDIDAD
	glEnable(GL_DEPTH_TEST);
}

void Render::setupObject(Object3D* obj)
{
	BufferObject buffer;

	objectList.push_back(obj);

	//EN EL BUFFER OBJECT QUE RESERVAMOS EN GPU CON EL GENVERTEXARRAYS, TENDREMOS TANTO EL BUFFER DE VERTICES COMO EL DE IDs
	glGenVertexArrays(1, &buffer.bufferId);
	glGenBuffers(1, &buffer.vertId);
	glGenBuffers(1, &buffer.listId);

	glBindVertexArray(buffer.bufferId);

	glBindBuffer(GL_ARRAY_BUFFER, buffer.vertId); // == LAS SIGUIENTES INSTRUCCIONES SON DE IDs
	glBufferData(GL_ARRAY_BUFFER, // == PARA EL ULTIMO BUFFER QUE ACTIVE, VOY A SUBIR DATOS
		obj->vertexList.size() * sizeof(Vertex),
		obj->vertexList.data(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.listId); //== LAS SIGUIENTES INSTRUCCIONES SON DE IDs
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, // == PARA EL ULTIMO BUFFER QUE ACTIVE, VOY A SUBIR DATOS
		obj->idList.size() * sizeof(unsigned int),
		obj->idList.data(),
		GL_STATIC_DRAW);

	bufferList[obj->id] = buffer;
}

void Render::putCamera(Camera* cam)
{
	camera = cam;
	proyectionMatrixAux = cam->perspective();
}

void Render::putLight(Light* light)
{
	this->light = light;
}

Light* Render::getLight()
{
	return this->light;
}


void Render::drawGL()
{
	Matrix4x4f viewMatrixAux = this->camera->view();
	BufferObject bo;

	for (auto& i : objectList) //iterador automatico?
	{
		i->updateModelMatrix();

		Matrix4x4f MVP =matrix4x4f::transverse(matrix4x4f::matrixProduct(proyectionMatrixAux, matrix4x4f::matrixProduct(viewMatrixAux, i->modelMatrix)));


		// LOS BUFFER OBJECTS COPIAN LOS DATOS DE LOS OBJECTOS DE CPU A GPU-----------------------------------
		
		//------------------------------BUSCAR SU BUFFER OBJECT-----------------------------------------------
		bo = bufferList[i->id];
		//Activar buffer object
		glBindVertexArray(bo.bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bo.vertId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.listId);

		//Decimos que vamos a usar el programa
		i->prg->use();

		//Le decimos al programa lo que tiene que guardar
		i->prg->setVertexPositions((void*)offsetof(Vertex, posicion));
		i->prg->setVertexColors((void*)offsetof(Vertex, color));
		i->prg->setVertexNormals((void*)offsetof(Vertex, normal));
		i->prg->setVertexUVs((void*)offsetof(Vertex, uv));
		
		i->prg->setMatrixMVP((float*)&MVP);
		i->prg->setMatrixM((float*)&i->modelMatrix);

		i->prg->setLight(*this->light);

		i->mat->bind(0);
		i->prg->setMaterial(*i->mat);


		/*glPushMatrix();
		glMultMatrixf((float*)&MVP);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(4, GL_FLOAT, sizeof(Vertex),
			(void*)offsetof(Vertex, posicion));*/

		//---------------------------HABILITA LOS COLORES-----------------------------------------------------
		/*glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_FLOAT, sizeof(Vertex),
			(void*)offsetof(Vertex, color));*/


		//---------------------------DESHABILITA EL CONTROL DE LOS BUFFERS SOBRE LOS COLORES------------------
		
		
		glDrawElements(GL_TRIANGLES, i->idList.size(), GL_UNSIGNED_INT, nullptr);
		
		/*glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glPopMatrix();*/
	}
}

void Render::mainLoop()
{
	//ESTO LEERA CONSTANTEMENTE EVENTOS DE TECLADO
	InputManager::initInputManager(window);

	while (!glfwWindowShouldClose(window))
	{
		//-----------------ACTIVAR LOS COLORES Y LA PROFUNDIDAD-----------------------------------------------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//ACTIVAR LOS EVENTOS
		glfwPollEvents();

		camera->Move(1.0);
		light->move(1.0);

		//CON ESTO LLAMAMOS AL MOVE DE CADA OBJETO Y ACTUALIZAMOS SU MATRIZ
		for (auto& i : objectList)
		{
			i->move(1.0);
		}

		//DIBUJAMOS LOS OBJETOS
		drawGL();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
}