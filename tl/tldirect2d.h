#pragma once
#include <Windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

namespace tl {
	namespace direct2d {
		inline bool ifInit = false;
		inline ID2D1Factory* factory = NULL;
		inline ID2D1HwndRenderTarget* renderTarget = NULL;
		inline ID2D1SolidColorBrush* brush = NULL;
		
		bool Init(HWND windowHandle);
		void ResizeRenderTarget(HWND windowHandle);
		void ResizeRenderTarget(int width, int height);
		void updateChanges();
	}
}