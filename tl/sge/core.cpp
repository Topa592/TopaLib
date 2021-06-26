#include "core.h"
#include "../tldirect2d.h"

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

namespace tl::sge::e::functions {
	namespace impl {
		namespace {
			std::vector<void (*)(void)> funcs;
		}
	}
}

void e::functions::addStatic(void (*Func)(void)) {
	impl::funcs.push_back(Func);
}

void e::functions::runAll() {
	size_t size = impl::funcs.size();
	for (size_t i = 0; i < size; i++) {
		impl::funcs[i]();
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

namespace {
	std::vector<void(*)(tl::sge::Click)> mouselisteners;
}

void tl::sge::e::mouseListeners::addStatic(void(*Func)(tl::sge::Click c)) {
	mouselisteners.push_back(Func);
}

void tl::sge::e::mouseListeners::runAll(const Click& click) {
	const int size = mouselisteners.size();
	for (int i = 0; i < size; i++) {
		mouselisteners[i](click);
	}
}
