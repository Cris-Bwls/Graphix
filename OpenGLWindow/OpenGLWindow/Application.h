#pragma once
class Application
{
public:
	Application();
	virtual ~Application();

	bool Run(char const* csName, int nWidth, int nHeight, bool bFullScreen);

	virtual bool StartUp() = 0;
	virtual bool Update() = 0;
	virtual bool Draw() = 0;
	virtual bool ShutDown() = 0;

	inline int GetScreenHeight() const { return m_nHeight; };
	inline int GetScreenWidth() const { return m_nWidth; };
	inline char const* GetName() { return m_csName; };

protected:
	const char* m_csName;
	int m_nHeight;
	int m_nWidth;
	bool m_bFullScreen;
	bool m_bRunning = true;
};

