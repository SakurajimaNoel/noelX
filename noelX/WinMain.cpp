#include "Game.h"
int WINAPI wWinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ PWSTR lpCmdLine,
	_In_ int nCmdShow) 
{
	hInstance;
	hPrevInstance;
	lpCmdLine;
	nCmdShow;
	return Game{}.start();
}