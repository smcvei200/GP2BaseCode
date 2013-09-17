#pragma once

#include <string>

using namespace std;

//Interface for a window, classes will implement this interface. This way
//we can create a Linux Window, a Mac Window, a PS3 window etc
class IWindow
{
public:
	//we always have to implement an empty virtual destructor when we define 
	//an interface in C++
	virtual ~IWindow(){};

	//pure virtual function, we must implement this in all base classes
	//init function, will initialise the window
	virtual bool init(const wstring &title,int width,int height,bool fullscreen)=0;
	
	//running
	virtual bool running()=0;

	//is full screen
	virtual bool isFullScreen()=0;
	
	//check window messages
	virtual bool checkForWindowMessages()=0;

	//get a handle to the window, some APIs require a handle(think of it as a pointer) to a
	//window
	virtual void* getHandleToWindow()=0;
};