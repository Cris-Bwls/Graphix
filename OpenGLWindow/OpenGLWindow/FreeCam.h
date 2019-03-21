#pragma once
#include "Camera.h"
class FreeCam :
	public Camera
{
public:
	FreeCam();
	~FreeCam();

	void Update(float fDeltaTime);

private:

	int mouseX;
	int mouseY;
	double scroll;
};

