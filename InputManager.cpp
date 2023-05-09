#include "InputManager.h"

void InputManager::keyboardManager(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		std::cout << "Tecla apretada\n";
		keysState[key] = true;
		break;
	}
	case GLFW_RELEASE:
	{
		std::cout << "Tecla soltada\n";
		keysState[key] = false;
		break;
	}
	}
}

void InputManager::mousePosManager(GLFWwindow* window, double xpos, double ypos)
{
	posMX = xpos;
	posMY = ypos;
	std::cout << "X: " << posMX << "; Y: " << posMY << "\n";
}

void InputManager::mouseButtonManager(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		std::cout << "Tecla apretada\n";
		mouseState[button] = true;
		break;
	}
	case GLFW_RELEASE:
	{
		std::cout << "Tecla soltada\n";
		mouseState[button] = false;
		break;
	}
	}
}

void InputManager::initInputManager(GLFWwindow* window)
{
	//INICIALIZAR EVENTOS
	glfwSetKeyCallback(window, keyboardManager);
	glfwSetCursorPosCallback(window, mousePosManager);
	glfwSetMouseButtonCallback(window, mouseButtonManager);
}