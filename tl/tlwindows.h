#pragma once
#include <Windows.h>
namespace tl {
	namespace windows {
		HWND InitWindow(WNDPROC WindowProc);
		HWND InitWindow(WNDPROC WindowProc, RECT windowSize, const wchar_t* title);
		void InitDirect2DWindow(WNDPROC WindowProc);
		void InitDirect2DWindow(WNDPROC WindowProc, RECT windowSize, const wchar_t* title);
	}
}