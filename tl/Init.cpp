#include "Init.h"
#include <Windows.h>

void tl::windows::Init(WNDPROC WindowProc) {}

void tl::windows::Init(WNDPROC WindowProc, const wchar_t* title, int wtop, int wleft, int wright, int wbottom) {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	//WNDCLASSEX& windowclass = tl::windows::windowConfig;
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = GetModuleHandle(0);
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassExW(&windowclass);

	RECT rect = { 0,0,600,600 };

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Title", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, windowclass.hInstance, 0);

	if (!windowHandle) return;

	ShowWindow(windowHandle, SW_SHOW);
	MSG message;
	bool done = false;
	while (!done) {
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) {
				done = true;
			}
			else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
	}
}

void tl::windows::InitDirect2d(WNDPROC WindowProc) {}

void tl::windows::InitDirect2d(WNDPROC WindowProc, const wchar_t* title, int wtop, int wleft, int wright, int wbottom) {}
