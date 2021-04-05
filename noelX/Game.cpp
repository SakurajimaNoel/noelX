#include "Game.h"

Game::Game():wnd(L"Big",640,480){}

int Game::start() 
{
	MSG msg = { 0 };
	

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				return msg.wParam;
			}
		}
		else
		{
			Game::update();
		}
		
	}

}

void Game::update()
{
	wnd.gfx().flipBackBuffer();
}