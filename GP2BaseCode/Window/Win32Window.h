#pragma once

//Win32 Window Header file
#include <Windows.h>
//string header from the C++ std library
#include <string>

//The header file for our windows interface
#include "Window.h"

//namespace std, this so we don't need to prefix all std library variables
// with std::
using namespace std;

//Our implementation of a Window, this is a win32 window
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

	//The window callback function, this called when a windows message
	//is available 
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
