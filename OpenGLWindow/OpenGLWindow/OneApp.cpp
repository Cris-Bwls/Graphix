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



OneApp::OneApp(){}
OneApp::~OneApp(){}

/*
	@brief Overloads baseclass StartUp, automatically called by baseclass
*/
bool OneApp::StartUp()
{
	if (glfwInit() == false)
		return false;

	// Create Window and allow resizing if not fullscreen
	glfwWindowHint(GLFW_RESIZABLE, !m_bFullScreen);
	m_Window = glfwCreateWindow(m_nWidth, m_nHeight, m_csName, nullptr, nullptr);

	if (m_Window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	
	// Load openGL functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		return false;
	}

	// Print OpenGL version
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	// Create Gizmos
	Gizmos::create(10000U, 10000U, 10000U, 10000U);

	// Create Input
	InputCreate();

	// Init camera
	m_Cam = new FreeCam();
	m_Cam->SetPosition(vec3(0));
	m_Cam->SetLookAt(vec3(10, 10, 10), vec3(0, 1, 0));
	m_Cam->MakePerspective(glm::pi<float>() * 0.25f,
		16 / 9.0f, 0.1f, 1000.0f);

	// Init Shader
	m_Shader = new PhongShader();
	m_Shader->SetLightCount(2);
	m_Shader->SetLightDiffuse(0, vec4(1,0,0,1));
	m_Shader->SetLight(1,
		{
			{0,0,1},			// Pos
			vec4(0, 1, 0, 1),	// Diffuse
			vec4(1.0f) * 2.0f	// Spec
		}
	);

	// Init Model
	m_ModelTransform =
	{
		0.5,0,0,0,
		0,0.5,0,0,
		0,0,0.5,0,
		0,0,0,1
	};

	// Scales the object
	float scale = 5;
	m_ModelTransform[3][3] = m_ModelTransform[3][3] / scale;

	// Load Model
	if (!m_Model.load("./object/soulspear/soulspear.obj", true, true))
		return false;

	// Move lights into position
	m_Shader->SetLightPos(0, vec3(m_ModelTransform[3]) + vec3(0, 3, 10));
	m_Shader->SetLightPos(1, vec3(m_ModelTransform[3]) + vec3(0, 3, -10));

	// Init PrevTime
	prevTime = glfwGetTime();
	return true;
}
/*
	@brief Overloads baseclass Update, automatically called by baseclass
*/
bool OneApp::Update()
{
	// Refresh Input
	InputRefresh();
	glfwPollEvents();

	// Calc DeltaTime
	currTime = glfwGetTime();
	double deltaTime = currTime - prevTime;
	prevTime = currTime;

	// Check running
	m_bRunning = (glfwWindowShouldClose(m_Window) == false &&
		glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

	// Update Camera
	m_Cam->Update((float)deltaTime);

	return true;
}
/*
	@brief Overloads baseclass Draw, automatically called by baseclass
*/
bool OneApp::Draw()
{
	// Clear GL colour buffer
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Clear Gizmos
	Gizmos::clear();

	// Create Ground Grid
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

	// Draw Model
	m_Shader->SetModelMatrix(m_ModelTransform);
	m_Shader->SetViewMatrix(m_Cam->GetView());
	m_Shader->SetMVP(m_Cam->GetProjectionView() * m_ModelTransform);

	m_Model.draw();

	// Draw Ground Grid
	Gizmos::draw(m_Cam->GetProjectionView());

	// Swap Buffers
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
	return true;
}
/*
	@brief Overloads baseclass ShutDown, automatically called by baseclass
*/
bool OneApp::ShutDown()
{
	delete m_Cam;
	delete m_Shader;
	InputDestroy();
	Gizmos::destroy();
	glfwTerminate();
	return true;
}
