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
		tl::graphics::BeginDraw();
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) {
				done = true;
			} else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		
		handleLButtonDown();
		impl::Graphics::clearScreen(impl::Graphics::backGroundColor);
		impl::drawAll();
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
		tl::utility::sleep::End(sge::Engine::Tickrate);
	}
}

void tl::sge::impl::drawButtons() {
	for (const impl::ButtonData& d : buttons) {
		tl::sge::Graphics::drawRect(d.area);
	}
}

void tl::sge::impl::drawGrids() {
	for (const impl::GridData& d : grids) {
		sge::Graphics::drawRect(d.area);
		float stepX = (float)(d.area.right - d.area.left) / (float)d.width;
		float stepY = (float)(d.area.bottom - d.area.top) / (float)d.height;
		sge::Point p1;
		sge::Point p2;
		p1.y = d.area.top;
		p2.y = d.area.bottom;
		for (int x = 1; x < d.width; x++) {
			int left = (int)(stepX * x + d.area.left);
			p1.x = left;
			p2.x = left;
			sge::Graphics::drawLine(p1, p2);
		}
		p1.x = d.area.left;
		p2.x = d.area.right;
		for (int y = 1; y < d.height; y++) {
			int top = (int)(stepY * y + d.area.top);
			p1.y = top;
			p2.y = top;
			sge::Graphics::drawLine(p1, p2);
		}
	}
}

void tl::sge::impl::drawAll() {
	impl::drawButtons();
	impl::drawGrids();
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
	for (const tl::sge::impl::GridData& d : grids) {
		if (d.area.left <= p.x && p.x <= d.area.right
			&& d.area.top <= p.y && p.y <= d.area.bottom) {
			float stepX = (float)(d.area.right - d.area.left) / (float)d.width;
			float stepY = (float)(d.area.bottom - d.area.top) / (float)d.height;
			int resultX = 0;
			int resultY = 0;
			sge::Point temp = { p.x - d.area.left, p.y - d.area.top };
			for (int x = 0; x < d.width; x++) {
				int left = (int)(stepX * x);
				int right = (int)(left + stepX);
				if (left <= temp.x && temp.x <= right) {
					resultX = x;
					break;
				}
			}
			for (int y = 0; y < d.height; y++) {
				int top = (int)(stepY * y);
				int bottom = (int)(top + stepY);
				if (top <= temp.y && temp.y <= bottom) {
					resultY = y;
					break;
				}
			}
			d.Func(p, resultX, resultY);
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
