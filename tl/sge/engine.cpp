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
		e::MouseInput(8, lParam);
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
		e::Inputs::resetInput();
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

		//e::Inputs::handleInput();
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

void tl::sge::e::Inputs::mouse::processActions() { //HACK needs more optimizing to support multiple clicks a tick
	tl::graphics::setBrush(1, 0, 0, 1);
	for (int i = 0; i < e::Inputs::mouse::size; i++) {
		const ClickData& c = e::Inputs::mouse::data[i];
		if (c.clicked == false) continue;
		e::mouseListeners::runAll(c.click);
	}
}

void tl::sge::e::MouseInput(const int& type, LPARAM lParam) {
	e::Inputs::mouse::Input(type, lParam);
	e::Mouse::update(Clicktype(type), lParam);
}

void tl::sge::e::MouseScroll(const WPARAM& wParam, const LPARAM& lParam) {
	int latestLength = GET_WHEEL_DELTA_WPARAM(wParam);
	int type = 0;
	if (latestLength < 0) type = 6;
	else if (latestLength > 0) type = 7;
	else return;
	e::Inputs::mouse::Scroll(type, lParam);
	e::Mouse::update(tl::sge::Clicktype(type), lParam);
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

void tl::sge::e::Inputs::handleInput() {
	e::Inputs::mouse::processActions();
}

void tl::sge::e::Inputs::resetInput() {
	for (ClickData& c : Inputs::mouse::data) {
		c.reset();
	}
}

void tl::sge::e::Graphics::clearScreen(Color c) {
	tl::graphics::ClearScreen(c.r, c.g, c.b);
}
