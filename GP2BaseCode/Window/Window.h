#pragma once

#include <string>

using namespace std;

class IWindow
{
public:
	virtual ~IWindow(){};

	virtual bool init(const wstring &title,int width,int height,bool fullscreen)=0;
	
	virtual bool running()=0;

	virtual bool isFullScreen()=0;
	
	virtual bool checkForWindowMessages()=0;

	virtual void* getHandleToWindow()=0;
};