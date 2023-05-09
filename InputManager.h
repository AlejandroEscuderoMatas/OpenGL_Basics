#pragma once

#define GLAD_ONLY_HEADERS
#include "common.h"

class InputManager
{
public:
	inline static std::map<int, bool> keysState;
	inline static double pushedX;
	inline static double pushedY;
	inline static double raisedX;
	inline static double raisedY;

	inline static std::map<int, bool> mouseState;
	inline static float posMX = 0.0f;
	inline static float posMY = 0.0f;

	static void keyboardManager(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePosManager(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonManager(GLFWwindow* window, int button, int action, int mods);
	static void initInputManager(GLFWwindow* window);
};