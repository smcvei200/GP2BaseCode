#include "GameApplication.h"

//should really check to see if we are on a windows platform
#include "../Window/Win32Window.h"

CGameApplication::CGameApplication(void)
{
	m_pWindow=NULL;
	m_GameOptionDesc.gameName=TEXT("Lab 1");
	m_GameOptionDesc.width=800;
	m_GameOptionDesc.height=640;
	m_GameOptionDesc.fullscreen=false;
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
bool CGameApplication::init()
{
	//Parse command line options and also config file

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
	//Create a Win32 Window
	m_pWindow=new CWin32Window();
	m_pWindow->init(m_GameOptionDesc.gameName,m_GameOptionDesc.width,m_GameOptionDesc.height,m_GameOptionDesc.fullscreen);
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