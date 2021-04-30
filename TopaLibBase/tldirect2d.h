#pragma once
#include <Windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

namespace tl {
	namespace direct2d {
		bool ifInit = false;
		ID2D1Factory* factory = NULL;
		ID2D1HwndRenderTarget* renderTarget = NULL;
		ID2D1SolidColorBrush* brush = NULL;
		bool Init(HWND windowHandle);
		void Shutdown();
	}
}