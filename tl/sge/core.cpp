#include "core.h"
#include "../tldirect2d.h"

using namespace tl::sge;

namespace tl::sge::e::functions {
	namespace impl {
		namespace {
			constexpr int size = 6;
			//std::vector<void (*)(void)> funcs;
			std::vector<void (*)(void)> funcs[size];
		}
	}
}

void e::functions::addStatic(void (*Func)(void), int order) {
	if (order < 0 || impl::size < order) return;
	impl::funcs[order].push_back(Func);
	//impl::funcs.push_back(Func);
}

void e::functions::runAll() {
	for (auto& funcs : impl::funcs) {
		size_t size = funcs.size();
		for (size_t i = 0; i < size; i++) {
			funcs[i]();
		}
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
	impl::RawInput& updating = impl::rawinputs[static_cast<int>(c)];
	updating.ifChanged = true;
	updating.lParam = lParam;
}

tl::sge::Click tl::sge::e::Mouse::getLatestClick(const tl::sge::Clicktype c) {
	impl::RawInput& latest = impl::rawinputs[static_cast<int>(c)];
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
	const auto& size = mouselisteners.size();
	for (int i = 0; i < size; i++) {
		mouselisteners[i](click);
	}
}
