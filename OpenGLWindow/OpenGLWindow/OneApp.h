#pragma once
#include "Application.h"
#include "Shader.h"
#include "Mesh.h"

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
	FreeCam* m_Cam;
	GLFWwindow* m_Window;

	ShaderProgram m_Shader;
	Mesh m_QuadMesh;
	glm::mat4 m_QuadTransform;
};

