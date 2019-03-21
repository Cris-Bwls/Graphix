#include "FreeCam.h"
#include "Input.h"


#define UP INPUT_KEY_W
#define DOWN INPUT_KEY_S
#define LEFT INPUT_KEY_A
#define RIGHT INPUT_KEY_D
#define MOUSE_BUTTON INPUT_MOUSE_BUTTON_RIGHT

#define MOVE 5.0f
#define SMALL 0.05f


FreeCam::FreeCam()
{
	Input::getInstance()->getMouseXY(&mouseX, &mouseY);
	scroll = Input::getInstance()->getMouseScroll();
}


FreeCam::~FreeCam()
{
}

void FreeCam::Update(float fDeltaTime)
{
	Input* input = Input::getInstance();

	//MOVE
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

	double newScroll = input->getMouseScroll();
	double scrollDiff = scroll - newScroll;
	scroll = newScroll;

	if (abs(scrollDiff) > 0)
		SetPosition(vec3(m_Transform[3]) + (vec3(m_Transform[2]) * MOVE * (float)scrollDiff) * fDeltaTime);

	//ROTATERY STUFF
	int x, y;
	input->getMouseXY(&x, &y);

	float fX = (mouseX - x) * fDeltaTime * SMALL;
	float fY = (mouseY - y) * fDeltaTime * SMALL;

	mouseX = x;
	mouseY = y;
	
	if (input->isMouseButtonDown(MOUSE_BUTTON))
	{
		Rotate(fY, vec3(1, 0, 0));
		Rotate(-fX, vec3(m_View * vec4(0, 1, 0, 0)));
	}

	UpdateProjectionView();
}
