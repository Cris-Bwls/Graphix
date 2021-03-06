#include "Application.h"
#include "Input.h"



Application::Application(){}
Application::~Application(){}

/*
	@brief Runs the application
	@param name of application
	@param width of window
	@param height of window
	@param if window should be fullscreen
	@return if ran successfully
*/
bool Application::Run(char const* csName, int nWidth, int nHeight, bool bFullScreen)
{
	m_csName = csName;
	m_nHeight = nHeight;
	m_nWidth = nWidth;
	m_bFullScreen = bFullScreen;

	if (!StartUp())
		return false;


	while (m_bRunning)
	{
		Input::getInstance()->clearStatus();

		if (!Update())
			return false;


		if (!Draw())
			return false;
	}


	if (!ShutDown())
		return false;

	return true;
}

void Application::InputCreate()
{
	Input::create();
}

void Application::InputRefresh()
{
	Input::getInstance()->clearStatus();
}

void Application::InputDestroy()
{
	Input::destroy();
}
