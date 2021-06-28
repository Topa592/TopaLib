#include "buttons.h"
#include "sgeinit_in.h"
#include "sge.h"
#include "core.h"
#include <vector>
namespace sge = tl::sge;
namespace {
	std::vector<sge::e::ButtonData> buttons;
	std::vector<sge::e::GridData> grids;

	void processButtons(sge::Click c) {
		const sge::Point& p = c.location;
		const size_t size = buttons.size();
		for (size_t i = 0; i < size; i++) {
			const sge::e::ButtonData& d = buttons[i];
			if (d.area.left <= p.x && p.x <= d.area.right
				&& d.area.top <= p.y && p.y <= d.area.bottom) {
				const sge::ButtonClick& temp = { d.area, c };
				d.Func(temp);
			}
		}
	}

	void processGrids(sge::Click c) {
		const sge::Point& p = c.location;
		const size_t size = grids.size();
		for (size_t i = 0; i < size; i++) {
			const sge::e::GridData& d = grids[i];
			if (d.area.left <= p.x && p.x <= d.area.right
				&& d.area.top <= p.y && p.y <= d.area.bottom) {
				float stepX = (float)(d.area.right - d.area.left) / (float)d.width;
				float stepY = (float)(d.area.bottom - d.area.top) / (float)d.height;
				int resultX = 0;
				int resultY = 0;
				sge::Rect area = { 0,0,0,0 };
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
				const sge::GridClick& temp = { area, resultX, resultY, c };
				d.Func(temp);
			}
		}
	}

	void drawGrids() {
		sge::Graphics::setBrush(sge::BasicColor::Red);
		for (const sge::e::GridData& d : grids) {
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

	void drawButtons() {
		sge::Graphics::setBrush(sge::BasicColor::Red);
		for (const sge::e::ButtonData& d : buttons) {
			tl::sge::Graphics::drawRect(d.area);
		}
	}
}

void tl::sge::init::Buttons() {
	e::functions::addStatic(drawButtons, 1);
	e::functions::addStatic(drawGrids, 1);
	sge::Create::MouseListener(processButtons);
	sge::Create::MouseListener(processGrids);
}

void tl::sge::e::CreateStaticButton(e::ButtonData d) {
	buttons.push_back(d);
}

void tl::sge::e::CreateStaticGrid(e::GridData d) {
	grids.push_back(d);
}
