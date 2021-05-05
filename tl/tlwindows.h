#pragma once
#include <Windows.h>
namespace tl {
	namespace windows {
		template <typename Func>
		HWND InitWindow(HINSTANCE& hInstance, int& nShowCmd, Func& func) {
			WNDCLASSEX windowclass;
			ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
			windowclass.cbSize = sizeof(WNDCLASSEX);
			windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
			windowclass.hInstance = hInstance;
			windowclass.lpfnWndProc = func;
			windowclass.lpszClassName = L"MainWindow";
			windowclass.style = CS_HREDRAW | CS_VREDRAW;

			RegisterClassExW(&windowclass);

			RECT rect = { 0,0,800,800 };

			AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

			HWND windowHandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Testing", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

			if (!windowHandle) return windowHandle;

			ShowWindow(windowHandle, nShowCmd);
			return windowHandle;
		}

		void resizeWindow(HWND windowHandle);
	}
}