#include "sge.h"
#include <Windows.h>
#include "../WindowProc.h"
#include "../Utility.h"
#include "../Graphics.h"
#include "../tlwindows.h"
#include <windowsx.h>
#include <string>
#include "sgeinit.h"
#include "input.h"

LRESULT CALLBACK tl::sge::e::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_SIZE:
		tl::windowProc::resize(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		e::input::mouseInput(0, lParam);
		return 0;
	case WM_MBUTTONDOWN:
		e::input::mouseInput(1, lParam);
		return 0;
	case WM_RBUTTONDOWN:
		e::input::mouseInput(2, lParam);
		return 0;
	case WM_LBUTTONUP:
		e::input::mouseInput(3, lParam);
		return 0;
	case WM_MBUTTONUP:
		e::input::mouseInput(4, lParam);
		return 0;
	case WM_RBUTTONUP:
		e::input::mouseInput(5, lParam);
		return 0;
	case WM_MOUSEWHEEL:
		e::input::mouseScroll(wParam, lParam);
		return 0;
	case WM_MOUSEMOVE:
		e::input::mouseInput(8, lParam);
		return 0;
	case WM_DESTROY: { PostQuitMessage(0); return 0; }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void tl::sge::e::mainLoop() {
	MSG message;
	tl::utility::ConsistantSleep sleep;
	tl::utility::Timer fpsMeter;
	int frameCount = 0;
	sge::init::All();
	while (!e::done) {
		sleep.Start();
		tl::graphics::BeginDraw();
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) {
				e::done = true;
			} else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		e::Graphics::clearScreen(e::Graphics::backGroundColor);
		//start

		e::functions::runAll();
		
		//end
		tl::graphics::EndDraw();
		if (e::done) break;
		frameCount++;
		if (fpsMeter.ifTimeReset(1000)) {
			tl::windows::SetTitle(std::to_wstring(frameCount).c_str());
			frameCount = 0;
		}
		sleep.End(sge::Engine::Tickrate);
	}
}

auto tl::sge::e::lParamToSGEPoint(LPARAM lParam)->tl::sge::Point {
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	return sge::Point(xPos, yPos);
}

auto tl::sge::e::getClientPos() -> tl::sge::Point {
	int x = 0, y = 0;
	tl::utility::windows::GetClientPos(x, y);
	return Point(x, y);
}

auto tl::sge::e::scrollToSGEPoint(LPARAM lParam) -> tl::sge::Point {
	tl::sge::Point p;
	p = tl::sge::e::lParamToSGEPoint(lParam);
	tl::sge::Point windowpos = tl::sge::e::getClientPos();
	p.x -= windowpos.x;
	p.y -= windowpos.y;
	return p;
}

void tl::sge::e::Graphics::clearScreen(Color c) {
	tl::graphics::ClearScreen(c.r, c.g, c.b);
}
