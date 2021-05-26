#include "impl.h"
#include <Windows.h>
#include "../../WindowProc.h"
#include "../../Utility.h"
#include "../../Graphics.h"
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_SIZE:
		tl::windowProc::resize(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		tl::sge::impl::LButtonDown(lParam);
		return 0;
	case WM_DESTROY: { PostQuitMessage(0); return 0; }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void tl::sge::impl::mainLoop(int(*Tick)(void)) {
	MSG message;
	bool done = false;
	while (!done) {
		tl::utility::sleep::Start();
		impl::Inputs::resetInput();
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) {
				done = true;
			} else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		handleLButtonDown();
		tl::graphics::BeginDraw();
		impl::Graphics::clearScreen(impl::Graphics::backGroundColor);
		drawButtons();
		int result = Tick();
		switch (result) {
		case 0:
			break;
		default:
			done = true;
			break;
		}
		tl::graphics::EndDraw();

		if (done) break;
		tl::utility::sleep::End(50);
	}
}

void tl::sge::impl::drawButtons() {
	for (const tl::sge::impl::ButtonData& d : buttons) {
		tl::sge::Graphics::drawRect(d.area);
	}
}

void tl::sge::impl::handleLButtonDown() {//HACK needs more optimizing to support multiple clicks a tick
	tl::graphics::setBrush(1, 0, 0, 1);
	const ClickData& c = impl::Inputs::mouseData[0];
	if (c.clicked == false) return;
	const sge::Point& p = c.location;
	for (const tl::sge::impl::ButtonData& d : buttons) { 
		if (d.area.left <= p.x && p.x <= d.area.right
			&& d.area.top <= p.y && p.y <= d.area.bottom) {
			d.Func(p);
		}
	}
}

void tl::sge::impl::LButtonDown(LPARAM lParam) {
	ClickData& c = impl::Inputs::mouseData[0];
	if (c.clicked == true) return;
	c.clicked = true;
	c.location = impl::lParamToSGEPoint(lParam);
}

auto tl::sge::impl::lParamToSGEPoint(LPARAM lParam)->tl::sge::Point {
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	return sge::Create::Point(xPos, yPos);
}

void tl::sge::impl::Inputs::resetInput() {
	for (ClickData& c : Inputs::mouseData) {
		c.reset();
	}
}

void tl::sge::impl::Graphics::clearScreen(Color c) {
	tl::graphics::ClearScreen(c.r, c.g, c.b);
}
