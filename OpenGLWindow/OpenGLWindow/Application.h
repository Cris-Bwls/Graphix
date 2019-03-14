#pragma once
class Application
{
public:
	Application();
	virtual ~Application();

	virtual bool StartUp() = 0;
	virtual bool Update() = 0;
	virtual bool Draw() = 0;
	virtual bool ShutDown() = 0;
};

