#pragma once
#include "Application.h"

#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>

class FreeCam;

class OneApp :
	public Application
{
public:
	OneApp();
	~OneApp();

	bool StartUp();
	bool Update();
	bool Draw();
	bool ShutDown();

private:
	FreeCam* m_cam;
	GLFWwindow* m_window;
};

