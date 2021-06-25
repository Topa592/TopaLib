#include "core.h"
#include "../tldirect2d.h"
void tl::sge::e::Inputs::mouse::processButtons() {
	for (int i = 0; i < e::Inputs::mouse::size; i++) {
		const ClickData& c = e::Inputs::mouse::data[i];
		if (c.clicked == false) continue;
		e::buttons::run(c);
	}
}

void tl::sge::e::Inputs::mouse::processGrids() {
	for (int i = 0; i < e::Inputs::mouse::size; i++) {
		const ClickData& c = data[i];
		if (c.clicked == false) continue;
		e::buttons::run(c);
		e::grids::run(c);
	}
}

void tl::sge::e::Inputs::mouse::Input(int type, LPARAM lParam) {
	ClickData& c = e::Inputs::mouse::data[type];
	if (c.clicked == true) return;
	c.clicked = true;
	c.click.location = e::lParamToSGEPoint(lParam);
}

void tl::sge::e::Inputs::mouse::Scroll(int type, LPARAM lParam) {
	ClickData& c = e::Inputs::mouse::data[type];
	if (c.clicked == true) return;
	c.clicked = true;
	c.click.location = sge::e::scrollToSGEPoint(lParam);
}

using namespace tl::sge;

namespace tl::sge::e::buttons::impl {
	namespace {
		std::vector<ButtonData> buttons;
	}
}

void e::buttons::addStatic(ButtonData button) {
	impl::buttons.push_back(button);
}

void e::buttons::drawAll() {
	sge::Graphics::setBrush(sge::BasicColor::Red);
	for (const e::ButtonData& d : impl::buttons) {
		tl::sge::Graphics::drawRect(d.area);
	}
}

void e::buttons::run(const ClickData& c) {
	const sge::Point& p = c.click.location;
	const size_t size = impl::buttons.size();
	for (size_t i = 0; i < size; i++) {
		const ButtonData& d = impl::buttons[i];
		if (d.area.left <= p.x && p.x <= d.area.right
			&& d.area.top <= p.y && p.y <= d.area.bottom) {
			const ButtonClick& temp = { d.area, c.click };
			d.Func(temp);
		}
	}
}

namespace tl::sge::e::grids::impl {
	namespace {
		std::vector<GridData> grids;
	}
}

void e::grids::addStatic(GridData grid) {
	impl::grids.push_back(grid);
}

void e::grids::drawAll() {
	sge::Graphics::setBrush(sge::BasicColor::Red);
	for (const e::GridData& d : impl::grids) {
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

void e::grids::run(const ClickData& c) {
	const sge::Point& p = c.click.location;
	const size_t size = impl::grids.size();
	for (size_t i = 0; i < size; i++) {
		const GridData& d = impl::grids[i];
		if (d.area.left <= p.x && p.x <= d.area.right
			&& d.area.top <= p.y && p.y <= d.area.bottom) {
			float stepX = (float)(d.area.right - d.area.left) / (float)d.width;
			float stepY = (float)(d.area.bottom - d.area.top) / (float)d.height;
			int resultX = 0;
			int resultY = 0;
			Rect area = { 0,0,0,0 };
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
			const GridClick& temp = { area, resultX, resultY, c.click };
			d.Func(temp);
		}
	}
}

namespace tl::sge::e::functions {
	namespace impl {
		namespace {
			std::vector<FuncData> funcs;
		}
	}
}

void e::functions::addStatic(FuncData func) {
	impl::funcs.push_back(func);
}

void e::functions::runAll() {
	size_t size = impl::funcs.size();
	for (size_t i = 0; i < size; i++) {
		impl::funcs[i].Func();
	}
}

namespace tl::sge::e::holdButtons {
	namespace impl {
		namespace {
			std::vector<ButtonHoldData> holdbuttons;
		}
	}
}

void tl::sge::e::holdButtons::addStatic(ButtonHoldData holdButton) {
	impl::holdbuttons.push_back(holdButton);
}

void tl::sge::e::holdButtons::drawAll() {
	
}

void tl::sge::e::holdButtons::run(const ClickData& c) {
	size_t size = impl::holdbuttons.size();
	for (size_t i = 0; i < size; i++) {
		//impl::holdbuttons[i].Func(c);
	}
}

namespace tl::sge::e::Mouse {
	namespace impl {
		namespace {
			struct RawInput {
				bool ifChanged = false;
				LPARAM lParam = 0;
				WPARAM wParam = 0;
				Click click = { Clicktype(Clicktype::None), {0,0} };
				RawInput(Clicktype type) {
					click.type = type;
				}
			};
			RawInput rawinputs[9] = {
				Clicktype::LDown,
				Clicktype::MDown,
				Clicktype::RDown,
				Clicktype::LUp,
				Clicktype::MUp,
				Clicktype::RUp,
				Clicktype::ScrollDown,
				Clicktype::ScrollUp,
				Clicktype::None
			};
		}
	}
}

void tl::sge::e::Mouse::update(const tl::sge::Clicktype& c, const LPARAM& lParam) {
	impl::RawInput updating = impl::rawinputs[static_cast<int>(c)];
	updating.ifChanged = true;
	updating.lParam = lParam;
}

tl::sge::Click tl::sge::e::Mouse::getLatestClick(const tl::sge::Clicktype c) {
	impl::RawInput latest = impl::rawinputs[static_cast<int>(c)];
	if (latest.ifChanged) {
		latest.ifChanged = false;
		const Clicktype& type = latest.click.type;
		//looks bit like a hack but is good enough since it's called at most once per type
		//to fix this switching off from using sge::Clicktype in implementation input but for
		//public header still have it
		switch (type) { 
		case tl::sge::Clicktype::LDown:
		case tl::sge::Clicktype::MDown:
		case tl::sge::Clicktype::RDown:
		case tl::sge::Clicktype::LUp:
		case tl::sge::Clicktype::MUp:
		case tl::sge::Clicktype::RUp:
		case tl::sge::Clicktype::None:
			latest.click.location = lParamToSGEPoint(latest.lParam);
			break;
		case tl::sge::Clicktype::ScrollDown:
		case tl::sge::Clicktype::ScrollUp:
			latest.click.location = scrollToSGEPoint(latest.lParam);
			break;
		}
	}
	return latest.click;
}
