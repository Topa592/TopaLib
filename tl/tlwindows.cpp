#include "tlwindows.h"
#include "tldirect2d.h"
#include "Graphics.h"
#include <cstdlib>

HWND tl::windows::InitWindow(WNDPROC WindowProc) {
	return tl::windows::InitWindow(WindowProc, { 0,0,800,800 }, NULL);
}

HWND tl::windows::InitWindow(WNDPROC WindowProc, RECT windowSize, const wchar_t* title) {
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = GetModuleHandle(0);
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassExW(&windowclass);
	
	RECT rect = windowSize;

	HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", title, WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, windowclass.hInstance, 0);
	
	if (!windowHandle) return windowHandle;

	ShowWindow(windowHandle, SW_SHOW);
	return windowHandle;
}

void tl::windows::InitDirect2DWindow(WNDPROC WindowProc) {
	tl::windows::InitDirect2DWindow(WindowProc, { 0,0,800,800 }, NULL);
}

void tl::windows::InitDirect2DWindow(WNDPROC WindowProc, RECT windowSize, const wchar_t* title) {
	HWND windowHandle = tl::windows::InitWindow(WindowProc, windowSize, title);
	if (!windowHandle) std::exit(EXIT_FAILURE);
	if (!tl::direct2d::Init(windowHandle)) std::exit(EXIT_FAILURE);
	tl::graphics::setBrush(1, 0, 0, 1);
}

void tl::windows::HideConsole() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

void tl::windows::SetTitle(const wchar_t* title) {
	SetWindowTextW(GetActiveWindow(), title);
}
