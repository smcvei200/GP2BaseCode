#pragma once

#include <string>

class IWindow;

using namespace std;

class CGameApplication
{
public:
	CGameApplication(void);
	virtual ~CGameApplication(void);
	virtual bool init(const wstring &gameName);
	void run();
	virtual void render();
	virtual void update();
private:
	bool initInput();
	bool initGame();
	bool initGraphics();
	bool initPhysics();

	bool initWindow();
private:
	IWindow * m_pWindow;
	wstring m_GameName;
};