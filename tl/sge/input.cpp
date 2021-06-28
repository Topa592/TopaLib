#include "input.h"
#include "sge.h"
#include "sgeinit_in.h"
using tl::sge::e::ClickData;
using tl::sge::Clicktype;
using tl::sge::Click;
namespace impl {
	namespace {
		struct RawInput {
			bool ifChanged = false;
			LPARAM lParam = 0;
			Click click = { Clicktype(Clicktype::None), {0,0} };
			RawInput(Clicktype type) {
				click.type = type;
			}
		};
		RawInput rawLastInputs[9] = {
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
		ClickData data[8] = {
				Clicktype::LDown,
				Clicktype::MDown,
				Clicktype::RDown,
				Clicktype::LUp,
				Clicktype::MUp,
				Clicktype::RUp,
				Clicktype::ScrollDown,
				Clicktype::ScrollUp
		};
		
	}
}

void reset() {
	for (ClickData& c : impl::data) {
		c.reset();
	}
}

void processInput() {
	for (const ClickData& c : impl::data) {
		if (!c.clicked) continue;
		tl::sge::e::mouseListeners::runAll(c.click);
	}
}

void tl::sge::init::Input() {
	e::functions::addStatic(reset, 5);
	e::functions::addStatic(processInput, 1);
}

void tl::sge::e::input::mouseInput(int type, LPARAM lParam) {
	//last
	impl::rawLastInputs->ifChanged = true;
	impl::rawLastInputs->lParam = lParam;
	//first
	ClickData& c = e::Inputs::mouse::data[type];
	if (c.clicked == true) return;
	c.clicked = true;
	c.click.location = e::lParamToSGEPoint(lParam);
}

void tl::sge::e::input::mouseScroll(WPARAM wParam, LPARAM lParam) {
	int latestLength = GET_WHEEL_DELTA_WPARAM(wParam);
	int type = 0;
	if (latestLength < 0) type = 6;
	else if (latestLength > 0) type = 7;
	else return;
	//last
	impl::rawLastInputs->ifChanged = true;
	impl::rawLastInputs->lParam = lParam;
	//first
	ClickData& c = e::Inputs::mouse::data[type];
	if (c.clicked == true) return;
	c.clicked = true;
	c.click.location = sge::e::scrollToSGEPoint(lParam);
}

const ClickData& tl::sge::e::input::getFirstMouseInput(const Clicktype& type) {
	return impl::data[static_cast<int>(type)];
}

const Click& tl::sge::e::input::getLastMouseInput(const Clicktype& type) {
	impl::RawInput& latest = impl::rawLastInputs[static_cast<int>(type)];
	if (latest.ifChanged) {
		latest.ifChanged = false;
		const Clicktype& type = latest.click.type;
		//looks bit like a hack but is good enough since it's called at most once per type
		//to fix this switching off from using sge::Clicktype in implementation input but for
		//public header still have it
		switch (type) {
		case Clicktype::LDown:
		case Clicktype::MDown:
		case Clicktype::RDown:
		case Clicktype::LUp:
		case Clicktype::MUp:
		case Clicktype::RUp:
		case Clicktype::None:
			latest.click.location = lParamToSGEPoint(latest.lParam);
			break;
		case Clicktype::ScrollDown:
		case Clicktype::ScrollUp:
			latest.click.location = scrollToSGEPoint(latest.lParam);
			break;
		}
	}
	return latest.click;
}

void tl::sge::e::input::mouseFuncForEach(void(*Func)(const Click& click)) {
	for (const ClickData& c : impl::data) {
		if (c.clicked) Func(c.click);
	}
}
