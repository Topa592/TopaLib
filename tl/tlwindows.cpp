#include "tlwindows.h"
#include "tldirect2d.h"

void tl::windows::resizeWindow(HWND windowHandle) {
	tl::direct2d::ResizeRenderTarget(windowHandle);
}
