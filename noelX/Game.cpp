#include "Game.h"

Game::Game():wnd(L"Big",1024,768){}

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
	wnd.gfx().clearBuffer(1.0, 0.5f, 0.25f);
	wnd.gfx().drawTriangle(time.getTime());
	wnd.gfx().flipBackBuffer();
}