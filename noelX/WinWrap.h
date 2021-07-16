#pragma once
#include<Windows.h>
#include <optional>
#include"Graphics.h"
#include "imgui\imgui_impl_win32.h"
class Window
{
public:
	Window(LPCWSTR wndName, const int width, const int height );
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Graphics& gfx();
private:
	// Meyer's singleton Pattern
	class WindowRegister
	{
	public:
		static LPCWSTR getName();
		static HINSTANCE getInstance();
		
	private:
		WindowRegister();
		~WindowRegister();
		WindowRegister(const WindowRegister&) = delete;  //disabling copy constructor
		WindowRegister& operator = (const WindowRegister&) = delete;
		LPCWSTR name = L"Arceus";
		HINSTANCE hInt;
		static WindowRegister wndRg;
	};
	
	HWND hWnd;
	static LRESULT CALLBACK msgHandlerAssign(HWND lhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT msgHandler(HWND lhWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	std::optional<Graphics> pGfx;  //lazy/deferred object initialisation
};