#pragma once
#include "core.h"
namespace tl {
	namespace sge {
		namespace e {
			namespace input {
				void mouseInput(int type, LPARAM lParam);
				void mouseScroll(WPARAM wParam, LPARAM lParam);
				const ClickData& getFirstMouseInput(const Clicktype& type);
				const Click& getLastMouseInput(const Clicktype& type);
				void mouseFuncForEach(void(*Func)(const Click& click));
			}
		}
	}
}