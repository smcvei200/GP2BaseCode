#pragma once

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
	bool initInput();
	bool initGame();
	bool initGraphics();
	bool initPhysics();

	bool initWindow();
private:
};