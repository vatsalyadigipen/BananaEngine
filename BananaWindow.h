#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;
struct GLFWMonitor;

struct WindowProps
{
	int Width = 0;
	int Heigth = 0;
	std::string Title;
};

struct FrameBufferProps
{
	int Width = 0;
	int Height = 0;
};

class BananaWindowHandler
{
public:
	~BananaWindowHandler();

	WindowProps m_Props;
	FrameBufferProps m_FrameBuffer;
	
	void Init();
	void Update();
	void ShutDown();
	bool ShouldClose();

	static BananaWindowHandler& getInstance();
	void SwapBuffers();
	GLFWwindow* GetCurrentContext();

private:
	BananaWindowHandler();

	static BananaWindowHandler* instance;

	// window pointers
	GLFWwindow* pWindow;
	GLFWMonitor* pMonitor;
	
	// glfw setup
	bool bGLFWSuccess;

	// properties
	bool bShouldClose;

	// member functions
	/*static void GLFWErrorCallback(int error, const char* description);
	static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);
	static void GLFWWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);*/
	static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		std::cout << "OpenGL Debug: ";//<< message << std::endl;
	}
};