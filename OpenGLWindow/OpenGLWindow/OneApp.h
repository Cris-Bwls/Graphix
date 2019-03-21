#pragma once
#include "Application.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"

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

	OBJMesh m_BunnyMesh;
	glm::mat4 m_BunnyTransform;

	Mesh m_QuadMesh;
	glm::mat4 m_QuadTransform;

	double prevTime;
	double currTime;
};

