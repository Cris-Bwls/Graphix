#pragma once
#include "Application.h"
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
};

