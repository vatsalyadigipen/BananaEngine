#include "EventManager.h"

#include <iostream>
#include <string>

#include "../GameManager.h"

std::vector<EventManager::KeyCallbackFunc> EventManager::RegisteredKeyCallbacks;

void EventManager::ErrorCallback(int error, const char* description)
{
	// Error Callback
	std::cout << "Error in GLFW: " << description << std::endl;
}

void EventManager::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	
	// Keyboard Key Callbacks Dispatches Methods registered in the callback vector
	DispatchKeyCallbacks(key, scancode, action, mods);
}

void EventManager::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	// TODO: Fix Resizing Window Bug
	// Called while resizing window
	std::cout << "Window being resized... ";
	std::cout << "Width: " << width << " | Height: " << height << std::endl;
}

void EventManager::RegisterForKeyCallback(KeyCallbackFunc func)
{
	// Registers methods into RegisterKeyCallbacks
	RegisteredKeyCallbacks.push_back(func);
}

void EventManager::DeregisterForKeyCallback(KeyCallbackFunc func)
{
	// TODO: Deregister Methods from RegisterKeyCallbacks vector
}

void EventManager::DispatchKeyCallbacks(int key, int scancode, int action, int mods)
{
	// Dispatches Events Based on Input Key Presses
	KeyCallbackEvent KCBEvent = KeyCallbackEvent(key, scancode, action, mods);
	
	for (KeyCallbackFunc func : RegisteredKeyCallbacks)
		func(KCBEvent);
}
