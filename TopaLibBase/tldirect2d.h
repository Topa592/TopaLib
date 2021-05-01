#pragma once
#include <Windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

namespace tl {
	namespace direct2d {
		inline bool ifInit;
		inline ID2D1Factory* factory;
		inline ID2D1HwndRenderTarget* renderTarget;
		inline ID2D1SolidColorBrush* brush;
		
		bool Init(HWND windowHandle);
		void Shutdown();
	}
}