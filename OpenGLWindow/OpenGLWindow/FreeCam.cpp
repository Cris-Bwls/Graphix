#include "FreeCam.h"
#include "Input.h"

// Input Key Codes
#define UP INPUT_KEY_W
#define DOWN INPUT_KEY_S
#define LEFT INPUT_KEY_A
#define RIGHT INPUT_KEY_D
#define MOUSE_BUTTON INPUT_MOUSE_BUTTON_RIGHT

// Movement Multipliers
#define MOVE 5.0f
#define SMALL 0.05f
#define SCROLL 10.0f


FreeCam::FreeCam()
{
	// Init mouse position and scroll
	Input::getInstance()->getMouseXY(&m_mouseX, &m_mouseY);
	m_scroll = Input::getInstance()->getMouseScroll();
}

FreeCam::~FreeCam()
{
}

/*
	@brief Overload of baseclass Update
	@param deltaTime
*/
void FreeCam::Update(float fDeltaTime)
{
	Input* input = Input::getInstance();

	//Move
	if (input->isKeyDown(UP))
	{
		SetPosition(vec3(m_Transform[3]) + (vec3(m_Transform[1]) * MOVE * fDeltaTime));
	}
	if (input->isKeyDown(DOWN))
	{
		SetPosition(vec3(m_Transform[3]) - (vec3(m_Transform[1]) * MOVE * fDeltaTime));
	}
	if (input->isKeyDown(LEFT))
	{
		SetPosition(vec3(m_Transform[3]) - (vec3(m_Transform[0]) * MOVE * fDeltaTime));
	}
	if (input->isKeyDown(RIGHT))
	{
		SetPosition(vec3(m_Transform[3]) + (vec3(m_Transform[0]) * MOVE * fDeltaTime));
	}

	//Scroll
	double newScroll = input->getMouseScroll();
	double scrollDiff = m_scroll - newScroll;
	m_scroll = newScroll;

	if (abs(scrollDiff) > 0)
		SetPosition(vec3(m_Transform[3]) + (vec3(m_Transform[2]) * SCROLL * (float)scrollDiff) * fDeltaTime);

	//Rotation
	int x, y;
	input->getMouseXY(&x, &y);

	float fX = (m_mouseX - x) * fDeltaTime * SMALL;
	float fY = (m_mouseY - y) * fDeltaTime * SMALL;

	m_mouseX = x;
	m_mouseY = y;
	
	if (input->isMouseButtonDown(MOUSE_BUTTON))
	{
		Rotate(fY, vec3(1, 0, 0));
		Rotate(-fX, vec3(m_View * vec4(0, 1, 0, 0)));
	}

	// Update 
	UpdateProjectionView();
}
