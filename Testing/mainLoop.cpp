#include "../TopaLib/All.h"
#include <Windows.h>
#include <thread>

extern Graphics graphics;
extern bool EngineOn;

bool updateInput() {
	bool changed = false;

	return changed;
}

void waitForInput() {
	//while (EngineOn && !updateInput()) {
	Sleep(50);
	//}
}

void updateGraphics() {
	graphics.BeginDraw();
	graphics.ClearScreen(0.0, 0.0, 0.7);
	graphics.EndDraw();
}

void mainLoop() {
	while (EngineOn) {
		updateGraphics();
		Sleep(50);
	}
}