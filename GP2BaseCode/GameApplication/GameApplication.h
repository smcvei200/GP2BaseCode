#pragma once

#include <string>

using namespace std;
//#define BOOST_ALL_NO_LIB

//Forward decleration of our Window Interface
class IWindow;
class IRenderer;

struct GameOptionsDesc
{
	wstring gameName;
	int width;
	int height;
	bool fullscreen;
};

using namespace std;

class CGameApplication
{
public:
	CGameApplication(void);
	virtual ~CGameApplication(void);
	virtual bool init();
	void run();
	virtual void render();
	virtual void update();
private:
	bool parseConfigFile();
	bool initInput();
	bool initGame();
	bool initGraphics();
	bool initPhysics();

	bool initWindow();
private:
	IWindow * m_pWindow;
	IRenderer * m_pRenderer;
	GameOptionsDesc m_GameOptionDesc;
	wstring m_ConfigFileName;
};