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
	m_Window = glfwCreateWindow(m_nWidth, m_nHeight, m_csName, nullptr, nullptr);

	if (m_Window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		return false;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	Gizmos::create(10000U, 10000U, 10000U, 10000U);

	InputCreate();

	m_Cam = new FreeCam();
	m_Cam->SetPosition(vec3(0));
	m_Cam->SetLookAt(vec3(10, 10, 10), vec3(0, 1, 0));
	m_Cam->MakePerspective(glm::pi<float>() * 0.25f,
		16 / 9.0f, 0.1f, 1000.0f);

	m_Light = new Light();

	m_Shader.loadShader((unsigned int)eShaderStage::VERTEX, "./shaders/phong.vert");
	m_Shader.loadShader((unsigned int)eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (!(m_Shader.link()))
	{
		printf("Shader Error: %s\n", m_Shader.getLastError());
		return false;
	}

	//m_QuadMesh.InitialiseQuad();
	m_QuadTransform =
	{
		0.5,0,0,0,
		0,0.5,0,0,
		0,0,0.5,0,
		0,0,0,1
	};

	if (!m_BunnyMesh.load("./soulspear/soulspear.obj", true, true))
		return false;

	m_BunnyTransform = m_QuadTransform;


	prevTime = glfwGetTime();
	return true;
}

bool OneApp::Update()
{
	InputRefresh();
	glfwPollEvents();

	currTime = glfwGetTime();
	double deltaTime = currTime - prevTime;
	prevTime = currTime;

	m_bRunning = (glfwWindowShouldClose(m_Window) == false &&
		glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS);


	// our game logic and update code goes here!
	// so does our render code!
	m_Cam->Update(deltaTime);
	m_Light->m_Direction = glm::normalize(vec3(cos(currTime * 2), sin(currTime * 2), 0));

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

	m_Shader.bind();
	m_Shader.bindUniform("ProjectionViewModel", m_Cam->GetProjectionView() * m_QuadTransform);
	m_Shader.bindUniform("LightDirection", m_Light->m_Direction);
	m_Shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_BunnyTransform)));

	//m_QuadMesh.Draw();
	m_BunnyMesh.draw();

	Gizmos::draw(m_Cam->GetProjectionView());

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
	return true;
}

bool OneApp::ShutDown()
{
	delete m_Light;
	delete m_Cam;
	InputDestroy();
	Gizmos::destroy();
	glfwTerminate();
	return true;
}
