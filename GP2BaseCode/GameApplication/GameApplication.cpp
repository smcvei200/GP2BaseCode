#include "GameApplication.h"

CGameApplication::CGameApplication(void)
{

}

CGameApplication::~CGameApplication(void)
{

}

//Init
//This initialises all subsystems
bool CGameApplication::init()
{
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
	return true;
}

void CGameApplication::run()
{

}

void CGameApplication::render()
{
 
}

void CGameApplication::update()
{
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