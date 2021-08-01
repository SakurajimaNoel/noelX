#pragma once
#include "WinWrap.h"
#include "Time.h"
#include "Cube.h"
#include "Skybox.h"
#include "Pyramid.h"
#include "GuiManager.h"
#include "Camera.h"
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
	Camera camera;
	std::optional<Cube>cube;
	std::optional<Skybox>skybox;
	std::optional<Pyramid>pyramid;
	float sliderVar = 0.0f;
	//std::optional<Cube>cube2;
};





