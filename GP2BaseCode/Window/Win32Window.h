#pragma once

#include <string>
#include <Windows.h>
#include "Window.h"

using namespace std;

class CWin32Window:public IWindow
{
public:
	CWin32Window(void);
	~CWin32Window(void);

	bool init(const wstring &title,int width,int height,bool fullscreen);
	
	bool running()
	{
		return m_bIsRunning;
	};

	bool isFullScreen()
	{
		return m_bIsFullScreen;
	};

	LRESULT CALLBACK wndProc( HWND hWnd, UINT uMsg, 
		WPARAM wParam, LPARAM lParam );
	
	bool checkForWindowMessages();

	void* getHandleToWindow()
	{
		return m_hWND;
	};
private:
	bool m_bIsRunning;
	bool m_bIsFullScreen;
	HWND m_hWND;

};
