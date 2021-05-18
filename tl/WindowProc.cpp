#include "WindowProc.h"
#include "Impl.h"
#include "tldirect2d.h"

#include <windowsx.h>

void tl::windowProc::mouseMove(LPARAM lParam) {
	int xPos = GET_X_LPARAM(lParam);
	int yPos = GET_Y_LPARAM(lParam);
	tl::impl::mouse::latestLocation = { xPos, yPos };
}

void tl::windowProc::resize(LPARAM lParam) {
	if (!tl::direct2d::ifInit) return;
	tl::direct2d::ResizeRenderTarget(
		LOWORD(lParam),
		HIWORD(lParam)
	);
}
