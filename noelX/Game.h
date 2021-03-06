#pragma once
#include "WinWrap.h"
#include "Time.h"
#include "Cube.h"
#include "Suzanne.h"
#include "Skybox.h"
#include "UnindexedCube.h"
#include "GuiManager.h"
#include "Camera.h"
#include "PointLight.h"


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
	PointLight pLight;
	std::optional<Cube>cube;   //cube = placeholder cube for lighting
	std::optional<UnindexedCube>ucube;
	std::optional<Suzanne>suzanne;
	std::optional<Skybox>skybox;
	float sliderVar = 0.0f;
	//std::optional<Cube>cube2;
};





