#pragma once
class Application
{
public:
	Application();
	virtual ~Application();

	/*
		@brief Runs the application
		@param name of application
		@param width of window
		@param height of window
		@param if window should be fullscreen
		@return if ran successfully
	*/
	bool Run(char const* csName, int nWidth, int nHeight, bool bFullScreen);

	/*
		@brief Gets the screen height
		@return The screen height
	*/
	inline int GetScreenHeight() const { return m_nHeight; };

	/*
		@brief Gets the screen width
		@return The screen width
	*/
	inline int GetScreenWidth() const { return m_nWidth; };

	/*
		@brief Gets name
		@return The name
	*/
	inline char const* GetName() { return m_csName; };

protected:

	/*
		@brief Initialises the application, pure virtual
	*/
	virtual bool StartUp() = 0;

	/*
		@brief Performs Update, pure virtual
	*/
	virtual bool Update() = 0;

	/*
		@brief Performs Draw, pure virtual
	*/
	virtual bool Draw() = 0;

	/*
		@brief Shutsdown the application, pure virtual
	*/
	virtual bool ShutDown() = 0;

	/*
		@brief Performs Input::create()
	*/
	void InputCreate();

	/*
		@brief Performs Input::refresh()
	*/
	void InputRefresh();

	/*
		@brief Performs Input::destroy()
	*/
	void InputDestroy();

	const char* m_csName;
	int m_nHeight;
	int m_nWidth;
	bool m_bFullScreen;
	bool m_bRunning = true;
};

