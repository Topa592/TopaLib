#include "All.h"
#include <Windows.h>
#include <thread>

extern Graphics graphics;
Input input;
GraphicsText text(&graphics);

bool updateInput() {
	if (input.getKey('A')) {
		graphics.DrawCircle(100, 100, 5);
	}
	if (input.getKey('W')) {
		graphics.DrawCircle(110, 90, 5);
	}
	if (input.getKey('S')) {
		graphics.DrawCircle(110, 100, 5);
	}
	if (input.getKey('D')) {
		graphics.DrawCircle(120, 100, 5);
	}

	return false;
}

class myGraphics {
public:
	int temp = 0;
	int temp2 = 0;

	void start() {
		graphics.setBrush(1, 1, 0, 1);
	}

	void updateFrame() {
		graphics.BeginDraw();
		graphics.ClearScreen(0.0, 0.0, 0.7);
		text.func();
		updateInput();

		for (int i = 0; i < 100; i++) {
			int x = rand() % 400 + 10;
			int y = rand() % 400 + 10;
			graphics.FillRect(x, y, x + 10, y + 10);
		}
		for (int i = 0; i < temp; i++) {
			graphics.FillRect(i * 10, 700, i * 10 + 4, 710);
		}
		for (int i = 0; i < temp2; i++) {
			graphics.FillRect(i * 10, 680, i * 10 + 4, 690);
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
	x.start();
	while (engineOn) {
		x.updateFrame();
		Sleep(20);
	}
}