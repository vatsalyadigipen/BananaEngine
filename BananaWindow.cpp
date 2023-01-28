#include "BananaWindow.h"

#include "Events/EventManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

BananaWindowHandler* BananaWindowHandler::instance = nullptr;

BananaWindowHandler::BananaWindowHandler()
	: bGLFWSuccess(false), pWindow(nullptr), pMonitor(nullptr), bShouldClose(false)
{}

BananaWindowHandler::~BananaWindowHandler()
{}

BananaWindowHandler& BananaWindowHandler::getInstance()
{
	static BananaWindowHandler instance;
	return instance;
}

void BananaWindowHandler::SwapBuffers()
{
	glfwSwapBuffers(pWindow);
}

GLFWwindow* BananaWindowHandler::GetCurrentContext() { return glfwGetCurrentContext(); }

void BananaWindowHandler::Init()
{
	// set default props if not initialized
	if (m_Props.Title.empty())
		m_Props.Title = "Untitled";

	if (m_Props.Heigth == 0)
		m_Props.Heigth = 480;

	if (m_Props.Width == 0)
		m_Props.Width = 640;

	// initialize glfw
	if (bGLFWSuccess)
	{
		std::cout << "GLFW is already initialized!";
		exit(EXIT_FAILURE);
	}
	
	glfwSetErrorCallback(EventManager::ErrorCallback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	bGLFWSuccess = true;

	// Initialize OpenGL Context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window
	pWindow = glfwCreateWindow(m_Props.Width, m_Props.Heigth, m_Props.Title.c_str(), NULL, NULL);
	if (!pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(pWindow);

	// Initialize glew (or other gl functions loader)
	GLenum glewError = glewInit();
	if (GLEW_OK != glewError)
	{
		std::cout << "Terminating program. Reason:" << std::endl;
		std::cout << "Error in GLEW: " << glewGetErrorString(glewError) << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	glfwSetWindowSizeCallback(pWindow, EventManager::WindowSizeCallback);
	glfwSetKeyCallback(pWindow, EventManager::KeyboardCallback);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

void BananaWindowHandler::Update()
{
	if (!pWindow)
	{
		std::cout << "Window has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}

	// this should not be responsibility of Window. Maybe something like a BufferDraw
	glfwGetFramebufferSize(pWindow, &m_FrameBuffer.Width, &m_FrameBuffer.Height);
	glViewport(0, 0, m_FrameBuffer.Width, m_FrameBuffer.Height);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	if (glfwWindowShouldClose(pWindow))
		bShouldClose = true;
}

void BananaWindowHandler::ShutDown()
{
	if (!pWindow)
	{
		std::cout << "Window can't shutdown because it has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}
	if(!bGLFWSuccess)
	{
		std::cout << "GLFW  can't shutdown because it has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwDestroyWindow(pWindow);
	glfwTerminate();
}

bool BananaWindowHandler::ShouldClose()
{ 
	return bShouldClose;
}
