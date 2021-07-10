#include "Game.h"

Game::Game():wnd(L"Big",1024,768){}

int Game::start() 
{
	MSG msg = { 0 };
	cube.emplace(wnd.gfx());
	cube2.emplace(wnd.gfx());
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
	cube.value().updateTransform(wnd.gfx(), time.getTime());
	wnd.gfx().draw();
	//cube2.value().updateTransform(wnd.gfx(), time.getTime() + 2.0f);
	//wnd.gfx().draw();

	//gui
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool show_demo = true;
	if (show_demo)
	{
		ImGui::ShowDemoWindow(&show_demo);
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//end


	wnd.gfx().flipBackBuffer();
}