#pragma once
#include "WinWrap.h"
#include "Time.h"
#include "Cube.h"
class Game
{
public:
	Game();
	int start();
private:
	void update();
	Window wnd;
	Time time;
	std::optional<Cube>cube;
	std::optional<Cube>cube2;
};





