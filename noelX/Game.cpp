#include "Game.h"

Game::Game():wnd(L"Big",1024,768){}

int Game::start() 
{
	MSG msg = { 0 };
	cube.emplace(wnd.gfx());
	ucube.emplace(wnd.gfx());
	skybox.emplace(wnd.gfx());

	//cube2.emplace(wnd.gfx());
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
	wnd.gfx().clearBuffer(sliderVar, 0.5f, 0.25f);

	wnd.gfx().SetCamera(camera.getMatrix());
	
	
	pLight.updateBuffer(wnd.gfx());
	ucube.value().updateTransform(wnd.gfx());
	ucube.value().bindAndDraw(wnd.gfx());
	cube.value().updateTransform(wnd.gfx(),pLight.pos);
	cube.value().bindAndDrawI(wnd.gfx());
	//cube2.value().updateTransform(wnd.gfx(), time.getTime() + 2.0f);
	//wnd.gfx().draw();
	wnd.gfx().updateDepthStencil(D3D11_COMPARISON_LESS_EQUAL);
	skybox.value().updateTransform(wnd.gfx());
	skybox.value().bindAndDrawI(wnd.gfx());
	
	wnd.gfx().updateDepthStencil(D3D11_COMPARISON_LESS);


	//gui
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool show_demo = true;
	if (show_demo)
	{
		ImGui::ShowDemoWindow(&show_demo);
	}

	if (ImGui::Begin("Test Window"))
	{
		ImGui::SliderFloat("Color", &sliderVar, 0.0f, 1.0f);
	}
	ImGui::End();

	camera.startCameraWindow();
	pLight.startLightWindow();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	//end


	wnd.gfx().flipBackBuffer();
}