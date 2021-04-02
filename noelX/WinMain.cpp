#include "WinWrap.h"


int WINAPI wWinMain(
	 HINSTANCE hInstance, 
	 HINSTANCE hPrevInstance, 
	 PWSTR lpCmdLine,
	 int nCmdShow) 
{
	Window wnd;
	Window wnd2;
	MSG msg = { 0 };
	BOOL mResult;

	while ((mResult = GetMessage(&msg, nullptr, 0, 0)) > 0) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (mResult == -1)
		return -1;
	else 
		return msg.wParam;
}