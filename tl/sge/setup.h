#pragma once
#include <Windows.h>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
namespace tl {
	namespace sge {
		namespace setup {
			void Init(int (*Tick)(void), _In_ int nShowCmd);
		}
	}
}