#include "All.h"
#include <Windows.h>
#include <thread>

extern GraphicsBase graphsBase;
Input input;


class GraphicsExtension {
public:
	ID2D1RenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

	void setBase(GraphicsBase& x) {
		brush = x.brush;
		renderTarget = x.renderTarget;
	}

	void DrawCircle(int x, int y, int radius) {
		renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 1);
	}

	void FillRect(int x1, int y1, int x2, int y2) {
		renderTarget->FillRectangle(D2D1::RectF(x1, y1, x2, y2), brush);
	}
};

GraphicsExtension graphics;

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
		graphics.brush->SetColor(D2D1::ColorF(1, 1, 0, 1));
	}

	void updateFrame() {
		graphics.renderTarget->BeginDraw();
		graphics.renderTarget->Clear(D2D1::ColorF(0, 0, 0.7));
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
		graphics.renderTarget->EndDraw();
		temp = ++temp % 60;
		if (temp == 0) temp2 = ++temp2 % 60;
	}
};



void updateGraphics() {

}

void mainLoop(HWND& windowsHandle, bool& engineOn) {
	graphics.setBase(graphsBase);
	myGraphics x;
	x.start();
	
	while (engineOn) {
		x.updateFrame();
		Sleep(20);
	}
}