#pragma once
#include <Windows.h>
namespace tl {
	namespace windows {
		HWND InitWindow(HINSTANCE& hInstance, int& nShowCmd, LRESULT(*WindowProc)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam));
		void InitDirect2DWindow(HINSTANCE& hInstance, int& nShowCmd, LRESULT(*WindowProc)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam));
	}
}