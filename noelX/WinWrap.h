#pragma once
#include<Windows.h>
class Window
{
public:
	Window();
	~Window();

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
	static LRESULT CALLBACK msgHandlerAssign(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT msgHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};