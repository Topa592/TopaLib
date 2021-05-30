#include "tlwindows.h"
#include "tldirect2d.h"
#include "Graphics.h"
#include <cstdlib>

HWND tl::windows::InitWindow(HINSTANCE& hInstance, int& nShowCmd, WNDPROC WindowProc) {
	return tl::windows::InitWindow(hInstance, nShowCmd, WindowProc, { 0,0,800,800 }, NULL);
}

HWND tl::windows::InitWindow(HINSTANCE& hInstance, int& nShowCmd, WNDPROC WindowProc, RECT windowSize, const wchar_t* title) {
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassExW(&windowclass);
	
	RECT rect = windowSize;

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", title, WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	
	if (!windowHandle) return windowHandle;

	ShowWindow(windowHandle, nShowCmd);
	return windowHandle;
}

void tl::windows::InitDirect2DWindow(HINSTANCE& hInstance, int& nShowCmd, WNDPROC WindowProc) {
	tl::windows::InitDirect2DWindow(hInstance, nShowCmd, WindowProc, { 0,0,800,800 }, NULL);
}

void tl::windows::InitDirect2DWindow(HINSTANCE& hInstance, int& nShowCmd, WNDPROC WindowProc, RECT windowSize, const wchar_t* title) {
	HWND windowHandle = tl::windows::InitWindow(hInstance, nShowCmd, WindowProc, windowSize, title);
	if (!windowHandle) std::exit(EXIT_FAILURE);
	if (!tl::direct2d::Init(windowHandle)) std::exit(EXIT_FAILURE);
	tl::graphics::setBrush(1, 0, 0, 1);
}
