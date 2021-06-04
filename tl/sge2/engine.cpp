#include "engine.h"
#include <Windows.h>
#include "../WindowProc.h"
#include "../Utility.h"
#include "../Graphics.h"
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (tl::sge2::core::Input::InputProc(hwnd, uMsg, wParam, lParam) == 0) return 0;
	switch (uMsg) {
	case WM_SIZE:
		tl::windowProc::resize(lParam);
		return 0;
	case WM_DESTROY: { PostQuitMessage(0); return 0; }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void tl::sge2::core::mainLoop(int(*Tick)(void)) {
	MSG message;
	while (!core::Engine::done) {
		tl::utility::sleep::Start();
		//Inputs::resetInput();
		tl::graphics::BeginDraw();
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) {
				core::Engine::done = true;
			} else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		core::Graphics::clearScreen(sge2::Engine::backgroundColor);
		for (auto& func : core::userFunctions) {
			func();
		}
		int result = Tick();
		tl::graphics::EndDraw();

		if (core::Engine::done) break;
		tl::utility::sleep::End(sge2::Engine::tickrate);
	}
}

