#include "Game.h"
int WINAPI wWinMain(
	 HINSTANCE hInstance, 
	 HINSTANCE hPrevInstance, 
	 PWSTR lpCmdLine,
	 int nCmdShow) 
{

	return Game{}.start();
}