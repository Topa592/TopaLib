#include "core.h"
#include <Windows.h>
#include <windowsx.h>
#include "geCore.h"
#include "../WindowProc.h"
#include "../Utility.h"
#include "../Graphics.h"
#include <vector>

namespace {
	static std::vector<void(*)(void)> staticTicks;
	void runTicks() {
		for (const auto& tick : staticTicks) {
			tick();
		}
	}
}

LRESULT CALLBACK tl::gecore::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_SIZE:
		tl::windowProc::resize(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		//tl::sge::impl::LButtonDown(lParam);
		return 0;
	case WM_DESTROY: { PostQuitMessage(0); return 0; }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void tl::gecore::mainLoop() {
	MSG message;
	bool done = false;
	while (!done) {
		tl::utility::sleep::Start();
		//impl::Inputs::resetInput();
		tl::graphics::BeginDraw();
		gecore::clearScreen(gecore::BackgroundColor);
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) {
				done = true;
			} else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		runTicks();
		
		tl::graphics::EndDraw();

		if (done) break;
		tl::utility::sleep::End(gecore::Tickrate);
	}
}

void tl::gecore::addStaticTick(void(*Func)(void)) {
	staticTicks.push_back(Func);
}

void tl::gecore::clearScreen(ge::Color c) {
	tl::graphics::ClearScreen(c.r, c.g, c.b);
}
