#include "../ph/sge/sgeWindowsApi.h"
#include "sgeWindowsApi_in.h"
#include "../Events.h"
namespace tl::sge::wa {
	namespace {
		tl::events::EventEmitter<HWND, UINT, WPARAM, LPARAM> messageEvents;
	}
	void AddMessageLoop(void(*messageLoop)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)) {
		messageEvents.add(messageLoop);
	}

	void Send(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		messageEvents.send(hwnd, uMsg, wParam, lParam);
	}
}
