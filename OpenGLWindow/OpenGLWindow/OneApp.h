#pragma once
#include "Application.h"
#include "LitShader.h"
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

	/*
		@brief Overloads baseclass StartUp, automatically called by baseclass
	*/
	bool StartUp();

	/*
		@brief Overloads baseclass Update, automatically called by baseclass
	*/
	bool Update();

	/*
		@brief Overloads baseclass Draw, automatically called by baseclass
	*/
	bool Draw();

	/*
		@brief Overloads baseclass ShutDown, automatically called by baseclass
	*/
	bool ShutDown();

private:
	FreeCam* m_Cam;
	GLFWwindow* m_Window;

	LitShader* m_Shader;

	OBJMesh m_Model;
	glm::mat4 m_ModelTransform;

	double prevTime;
	double currTime;
};

