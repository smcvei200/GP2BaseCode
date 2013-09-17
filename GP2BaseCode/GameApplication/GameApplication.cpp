#include "GameApplication.h"

//should really check to see if we are on a windows platform
#include "../Window/Win32Window.h"

CGameApplication::CGameApplication(void)
{
	m_pWindow=NULL;
}

CGameApplication::~CGameApplication(void)
{
	if (m_pWindow)
	{
		delete m_pWindow;
		m_pWindow=NULL;
	}
}

//Init
//This initialises all subsystems
bool CGameApplication::init(const wstring &gameName)
{
	m_GameName=gameName;
	if (!initWindow())
		return false;
	if (!initGraphics())
		return false;
	if (!initInput())
		return false;
	if (!initGame())
		return false;
	return true;
}

bool CGameApplication::initGame()
{
	m_pWindow=new CWin32Window();
	//should all come from a config file
	m_pWindow->init(m_GameName,800,640,false);
	return true;
}

void CGameApplication::run()
{
	while(m_pWindow->running())
	{
		m_pWindow->checkForWindowMessages();
		update();
		render();
	}
}

void CGameApplication::render()
{
 
}

void CGameApplication::update()
{
}

bool CGameApplication::initInput()
{
	return true;
}

bool CGameApplication::initPhysics()
{
	return true;
}
//initGraphics - initialise the graphics subsystem - BMD
bool CGameApplication::initGraphics()
{
	return true;
}

bool CGameApplication::initWindow()
{
	return true;
}