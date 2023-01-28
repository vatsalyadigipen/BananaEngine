#pragma once

#include <glfw/glfw3.h>
#include <vector>
#include "KeyCallbackEvent.h"

class GameObject;

class EventManager
{
public:
	static void ErrorCallback(int error, const char* description);
	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void WindowSizeCallback(GLFWwindow* window, int width, int height);
	
public:
	typedef void (*KeyCallbackFunc)(KeyCallbackEvent);
	static void RegisterForKeyCallback(KeyCallbackFunc func);
	static void DeregisterForKeyCallback(KeyCallbackFunc func);

private:
	static std::vector<KeyCallbackFunc> RegisteredKeyCallbacks;

private:
	static void DispatchKeyCallbacks(int key, int scancode, int action, int mods);
};