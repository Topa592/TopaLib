#include "ge.h"

void tl::ge::addStaticTick(void(*Func)(void)) {
	ge::staticUserTicks.push_back(Func);
}

void tl::ge::engineTick() {

	ge::runUser();
}

void tl::ge::runUser() {
	for (const auto& f : ge::staticUserTicks) {
		f();
	}
}
