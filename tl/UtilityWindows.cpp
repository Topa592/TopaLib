#include "Utility.h"
#include <Windows.h>

void tl::utility::windows::GetClientPos(int& x, int& y) {
	POINT p = { NULL };
	HWND hwnd = GetActiveWindow();
	if (ClientToScreen(hwnd, &p)) {
		x = p.x;
		y = p.y;
	}
}