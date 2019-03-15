#include "OneApp.h"

#include <iostream>
#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include"FreeCam.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;



OneApp::OneApp()
{
}


OneApp::~OneApp()
{
}

bool OneApp::StartUp()
{
	if (glfwInit() == false)
		return false;


	glfwWindowHint(GLFW_RESIZABLE, !m_bFullScreen);
	m_window = glfwCreateWindow(m_nWidth, m_nHeight, m_csName, nullptr, nullptr);

	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	Gizmos::create(255U, 255U, 255U, 255U);

	m_cam = new FreeCam();
	m_cam->SetPosition(vec3(0));
	m_cam->SetLookAt(vec3(10, 10, 10), vec3(0, 1, 0));
	m_cam->MakePerspective(glm::pi<float>() * 0.25f,
		16 / 9.0f, 0.1f, 1000.0f);

	return true;
}

bool OneApp::Update()
{

	m_bRunning = (glfwWindowShouldClose(m_window) == false &&
		glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS);


	// our game logic and update code goes here!
	// so does our render code!
	m_cam->Update(0);

	return true;
}

bool OneApp::Draw()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	Gizmos::draw(m_cam->GetProjectionView());

	glfwSwapBuffers(m_window);
	glfwPollEvents();
	return true;
}

bool OneApp::ShutDown()
{
	delete m_cam;
	Gizmos::destroy();
	glfwTerminate();
	return true;
}
