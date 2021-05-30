#pragma once
#include <Windows.h>
namespace tl {
	namespace windows {
		HWND InitWindow(HINSTANCE& hInstance, int& nShowCmd, WNDPROC WindowProc);
		HWND InitWindow(HINSTANCE& hInstance, int& nShowCmd, WNDPROC WindowProc, RECT windowSize, const wchar_t* title);
		void InitDirect2DWindow(HINSTANCE& hInstance, int& nShowCmd, WNDPROC WindowProc);
		void InitDirect2DWindow(HINSTANCE& hInstance, int& nShowCmd, WNDPROC WindowProc, RECT windowSize, const wchar_t* title);
	}
}