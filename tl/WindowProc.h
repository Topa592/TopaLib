#pragma once
#include <Windows.h>
namespace tl {
	namespace windowProc {
		void mouseMove(LPARAM lParam);
		void resize(LPARAM lParam);
		namespace mouse {
			void Move(LPARAM lParam);
			void ButtonDown(LPARAM lParam, WPARAM wParam);
			void ButtonUp(LPARAM lParam, WPARAM wParam);
			void ButtonDoubleClick(LPARAM lParam, WPARAM wParam);
		}
	}
}