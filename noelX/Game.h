#pragma once
#include "WinWrap.h"
#include "Time.h"
#include "Cube.h"
#include "GuiManager.h"
class Game
{
public:
	Game();
	int start();
private:
	void update();
	GuiManager guiManager;
	Window wnd;
	Time time;
	std::optional<Cube>cube;
	std::optional<Cube>cube2;
};





