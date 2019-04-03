#include "OneApp.h"

#include <iostream>
#include "Gizmos.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include"FreeCam.h"

#include "PhongShader.h"

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

	m_Shader = new PhongShader();
	//m_Shader->Use();
	//m_Shader->SetLightCount(1);
	//m_Shader->SetLight(0,
	//	{
	//		{0,0,1},			// Pos
	//		vec4(1) * .5f,	// Diffuse
	//		vec4(1) * .5f	// Spec
	//	}
	//);

	//m_Shader->Use();
	//m_Shader->AddLight(
	//	{
	//		{0,0,1},			// Pos
	//		vec4(1.0f) * 0.5f,	// Diffuse
	//		vec4(1.0f) * 2.0f	// Spec
	//	}
	//);
	//m_Shader->AddLight(
	//	{
	//		{0,20,-20}, // Pos
	//		vec4(1.0f), // Diffuse
	//		vec4(1.0f)  // Spec
	//	}
	//);
	//m_Shader->AddLight(
	//	{
	//		{30,0,0},			// Pos
	//		vec4(1.0f) * .5f,	// Diffuse
	//		vec4(1.0f) * .5f	// Spec
	//	}
	//);
	//m_Shader->loadShader((unsigned int)eShaderStage::VERTEX, "./shaders/phong.vert");
	//m_Shader->loadShader((unsigned int)eShaderStage::FRAGMENT, "./shaders/phong.frag");

	//m_Shader->Use();

	//if (!(m_Shader->link()))
	//{
	//	printf("Shader Error: %s\n", m_Shader->getLastError());
	//	return false;
	//}

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

	//m_Shader->Use();
	//m_Shader->SetLightCount(1);
	//m_Shader->SetLightPos(0, vec3(0,0,0));
	//m_Shader->SetLightDiffuse(0, vec4(1,1,1,1));
	//m_Shader->SetLightSpecular(0, vec4(1,1,1,1));

	//m_Shader->Use();
	//m_Shader->SetLight(0, { {10.0f,10.0f,10.0f}, vec4(1), vec4(1) });

	m_Shader->SetModelMatrix(m_QuadTransform);
	m_Shader->SetViewMatrix(m_Cam->GetView());
	m_Shader->SetMVP(m_Cam->GetProjectionView() * m_QuadTransform);
	//m_Shader->SetNormalMatrix(glm::inverseTranspose(glm::mat3(m_BunnyTransform)));

	m_BunnyMesh.draw();
	//m_QuadMesh.Draw();

	Gizmos::draw(m_Cam->GetProjectionView());

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
	return true;
}

bool OneApp::ShutDown()
{
	delete m_Cam;
	delete m_Shader;
	InputDestroy();
	Gizmos::destroy();
	glfwTerminate();
	return true;
}
