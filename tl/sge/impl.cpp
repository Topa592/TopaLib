#include "sge.h"
#include <Windows.h>
#include "../WindowProc.h"
#include "../Utility.h"
#include "../Graphics.h"
#include <windowsx.h>

LRESULT CALLBACK tl::sge::impl::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_SIZE:
		tl::windowProc::resize(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		tl::sge::impl::MouseInput(0, lParam);
		return 0;
	case WM_MBUTTONDOWN:
		tl::sge::impl::MouseInput(1, lParam);
		return 0;
	case WM_RBUTTONDOWN:
		tl::sge::impl::MouseInput(2, lParam);
		return 0;
	case WM_LBUTTONUP:
		tl::sge::impl::MouseInput(3, lParam);
		return 0;
	case WM_MBUTTONUP:
		tl::sge::impl::MouseInput(4, lParam);
		return 0;
	case WM_RBUTTONUP:
		tl::sge::impl::MouseInput(5, lParam);
		return 0;
	case WM_DESTROY: { PostQuitMessage(0); return 0; }
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void tl::sge::impl::mainLoop(int(*Tick)(void)) {
	MSG message;
	while (!impl::done) {
		tl::utility::sleep::Start();
		impl::Inputs::resetInput();
		tl::graphics::BeginDraw();
		while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) {
				impl::done = true;
			} else {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		
		handleMouse();
		impl::Graphics::clearScreen(impl::Graphics::backGroundColor);
		impl::drawAll();
		int result = Tick();
		switch (result) {
		case 0:
			break;
		default:
			impl::done = true;
			break;
		}
		tl::graphics::EndDraw();

		if (impl::done) break;
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

void tl::sge::impl::handleMouse() {//HACK needs more optimizing to support multiple clicks a tick
	tl::graphics::setBrush(1, 0, 0, 1);
	for (int i = 0; i < impl::Inputs::mouseDataSize; i++) {
		ClickData& c = impl::Inputs::mouseData[i];
		if (c.clicked == false) continue;
		const sge::Click& click = { sge::Clicktype(i), c.location };
		const sge::Point& p = c.location;
		for (const tl::sge::impl::ButtonData& d : buttons) {
			if (d.area.left <= p.x && p.x <= d.area.right
				&& d.area.top <= p.y && p.y <= d.area.bottom) {
				const ButtonClick& temp = { d.area, click };
				d.Func(temp);
			}
		}
		for (const tl::sge::impl::GridData& d : grids) {
			if (d.area.left <= p.x && p.x <= d.area.right
				&& d.area.top <= p.y && p.y <= d.area.bottom) {
				float stepX = (float)(d.area.right - d.area.left) / (float)d.width;
				float stepY = (float)(d.area.bottom - d.area.top) / (float)d.height;
				int resultX = 0;
				int resultY = 0;
				Rect area;
				for (int x = 0; x < d.width; x++) {
					area.left = (int)(stepX * x) + d.area.left;
					area.right = (int)(area.left + stepX);
					if (area.left <= p.x && p.x <= area.right) {
						resultX = x;
						break;
					}
				}
				for (int y = 0; y < d.height; y++) {
					area.top = (int)(stepY * y) + d.area.top;
					area.bottom = (int)(area.top + stepY);
					if (area.top <= p.y && p.y <= area.bottom) {
						resultY = y;
						break;
					}
				}
				const GridClick& temp = { area, resultX, resultY, click };
				d.Func(temp);
			}
		}
	}
}

void tl::sge::impl::MouseInput(int type, LPARAM lParam) {
	ClickData& c = impl::Inputs::mouseData[type];
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
