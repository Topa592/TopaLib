#include "All.h"
#include "mainClass.h"

#include <Windows.h>



void mainLoop(HWND& windowHandle, bool& engineOn, GraphicsBase& graphics) {
	mainClass x(windowHandle, graphics);
	while (engineOn) {
		x.oneTick();
		Sleep(20);
	}
}