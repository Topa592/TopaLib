#include "WindowProc.h"
#include "Impl.h"
#include "tldirect2d.h"

#include <windowsx.h>

namespace {
	auto getMousePosition(const LPARAM& lParam)->tl::datatypes::Point {
		return {
			GET_X_LPARAM(lParam),
			GET_Y_LPARAM(lParam)
		};
	}

	void updateMousePosition(const LPARAM& lParam) {
		tl::impl::mouse::latestLocation = getMousePosition(lParam);
	}
}

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

void tl::windowProc::mouse::Move(LPARAM lParam) {
	updateMousePosition(lParam);
}

void tl::windowProc::mouse::ButtonDown(LPARAM lParam, WPARAM wParam) {
	
}

void tl::windowProc::mouse::ButtonUp(LPARAM lParam, WPARAM wParam) {

}

void tl::windowProc::mouse::ButtonDoubleClick(LPARAM lParam, WPARAM wParam) {

}
