#include "../TopaLib/All.h"
#include <Windows.h>
#include <thread>

extern Graphics graphics;
Input input;

bool updateInput() {
	if (input.getKey('A')) {
		graphics.DrawCircle(100, 100, 10);
	}

	return false;
}

void waitForInput() {
	//while (engineOn && !updateInput()) {
	Sleep(50);
	//}
}

class myGraphics {
public:
	int temp = 0;
	int temp2 = 0;
	myGraphics() {
		graphics.setBrush(1, 1, 0, 1);
	}

	void updateFrame() {
		graphics.BeginDraw();
		graphics.ClearScreen(0.0, 0.0, 0.7);
		updateInput();
		for (int i = 0; i < temp; i++) {
			graphics.DrawRect(i * 10, 700, i * 10, 710);
		}
		for (int i = 0; i < temp2; i++) {
			graphics.DrawRect(i * 10, 680, i * 10, 690);
		}
		graphics.EndDraw();
		temp = ++temp % 60;
		if (temp == 0) temp2 = ++temp2 % 60;
	}
};



void updateGraphics() {
	
}

void mainLoop(HWND& windowsHandle, bool& engineOn) {
	myGraphics x;
	while (engineOn) {
		x.updateFrame();
		Sleep(20);
	}
}