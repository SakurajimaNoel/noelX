#pragma once
#include "WinWrap.h"
#include "Time.h"
class Game
{
public:
	Game();
	int start();
private:
	void update();
	Window wnd;
	Time time;
};





