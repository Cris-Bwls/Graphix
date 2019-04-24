#pragma once
#include "Camera.h"
class FreeCam :
	public Camera
{
public:
	FreeCam();
	~FreeCam();

	/*
		@brief Overload of baseclass Update
		@param deltaTime
	*/
	void Update(float fDeltaTime);

private:

	int m_mouseX;
	int m_mouseY;
	double m_scroll;
};

