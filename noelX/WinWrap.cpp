#include "WinWrap.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


Window::WindowRegister Window::WindowRegister::wndRg;   //linker error without this

LPCWSTR Window::WindowRegister::getName() 
{
	return wndRg.name;
}

HINSTANCE Window::WindowRegister::getInstance() 
{
	return wndRg.hInt;
}

Graphics& Window::gfx()
{
	return *pGfx;
}

Window::WindowRegister::WindowRegister():hInt(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = Window::msgHandlerAssign;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszClassName = getName();
	wc.lpszMenuName = nullptr;

	RegisterClassEx(&wc);
}

Window::WindowRegister::~WindowRegister()
{
	UnregisterClass(getName(),getInstance());
}

Window::Window(LPCWSTR wndName, const int width, const int height)
{
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = width ;
	r.bottom = height ;
	AdjustWindowRect(&r, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	hWnd = CreateWindowEx(
		0,
		WindowRegister::getName(),
		wndName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0, 0,
		r.right - r.left, r.bottom - r.top,
		nullptr,
		nullptr,
		WindowRegister::getInstance(),
		this);
	ShowWindow(hWnd, SW_SHOW);
	ImGui_ImplWin32_Init(hWnd);  //gui win32 init
	pGfx.emplace(hWnd);
}

Window::~Window()
{
	ImGui_ImplWin32_Shutdown();
	DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::msgHandlerAssign(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	Window* pWnd = nullptr;
	if (uMsg == WM_NCCREATE) 
	{
		CREATESTRUCTW* pStruct = (CREATESTRUCTW*)lParam;
		pWnd = (Window*)pStruct->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWnd);
	}
	else
	{
		pWnd = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (pWnd)
	{
		return pWnd->msgHandler(hWnd, uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
}

LRESULT Window::msgHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(420);
		return 0;
	case WM_KEYDOWN:
		if (wParam == 'F') SetWindowText(hWnd, L"hello");
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
