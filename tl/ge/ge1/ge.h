#pragma once
#include <vector>
namespace tl {
	namespace ge {
		inline std::vector<void (*)(void)> staticUserTicks;
		void addStaticTick(void (*Func)(void));
		void engineTick();
		void runUser();
	}
}