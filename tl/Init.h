#pragma once
#include <Windows.h>
namespace tl {
	namespace windows {
		void Init(WNDPROC WindowProc);
		void Init(WNDPROC WindowProc, const wchar_t* title, int wtop, int wleft, int wright, int wbottom);
		void InitDirect2d(WNDPROC WindowProc);
		void InitDirect2d(WNDPROC WindowProc, const wchar_t* title, int wtop, int wleft, int wright, int wbottom);
	}
}