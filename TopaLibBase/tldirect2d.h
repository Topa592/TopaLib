#pragma once
#include <Windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")

namespace tl {
	namespace direct2d {
<<<<<<< HEAD
		inline bool ifInit;
		inline ID2D1Factory* factory;
		inline ID2D1HwndRenderTarget* renderTarget;
		inline ID2D1SolidColorBrush* brush;
		
=======
		bool ifInit = false;
		ID2D1Factory* factory = NULL;
		ID2D1HwndRenderTarget* renderTarget = NULL;
		ID2D1SolidColorBrush* brush = NULL;
>>>>>>> d06e6c294d730edae9143b4e6c28e8974d628b00
		bool Init(HWND windowHandle);
		void Shutdown();
	}
}