#include "GameApplication.h"

//should really check to see if we are on a windows platform
#include "../Window/Win32Window.h"

//boost header for program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;


CGameApplication::CGameApplication(void)
{
	m_pWindow=NULL;
	m_GameOptionDesc.gameName=TEXT("GP2");
	m_GameOptionDesc.width=800;
	m_GameOptionDesc.height=640;
	m_GameOptionDesc.fullscreen=false;
	m_ConfigFileName=TEXT("game.cfg");
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
	//Parse command line options and also config file(need to build boost)
	 po::options_description config("Configuration");
	 config.add_options()
		 ("GameName",po::value<string>(),"Game Title");
		 /*
		 ("WindowWidth",po::value<int>(&config)->default_value(m_GameOptionDesc.width),"Width of the Game window")
		 ("WindowHeight",po::value<int>(&config)->default_value(m_GameOptionDesc.height),"Width of the Game window")
		 ("Fullscreen",po::value<float>(&config)->default_value(m_GameOptionDesc.fullscreen),"Fullscreen window");*/

	if(!parseConfigFile())
		return false;
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

bool CGameApplication::parseConfigFile()
{
	//does the file exist?

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