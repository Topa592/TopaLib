#pragma once

#include "All.h"

class mainClass {
private:
	Input input;

	int x = 100;
	int y = 100;

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

	class Graphics {
	private:
		ID2D1HwndRenderTarget* renderTarget;
		ID2D1SolidColorBrush* brush;
	public:
		Graphics(GraphicsBase& base) {
			brush = base.brush;
			renderTarget = base.renderTarget;
			setBrush(1, 1, 0, 1);
		}

		void BeginDraw() { renderTarget->BeginDraw(); }
		void EndDraw() { renderTarget->EndDraw(); }

		void setBrush(float r, float g, float b, float a) {
			brush->SetColor(D2D1::ColorF(r, g, b, a));
		}

		void ClearScreen(float r, float g, float b) {
			renderTarget->Clear(D2D1::ColorF(r, g, b));
		}

		void ClearScreen() {
			renderTarget->Clear();
		}

		void DrawLine(float x1, float y1, float x2, float y2) {
			renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 1.0f);
		}

		void DrawCircle(float x, float y, float radius) {
			renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
		}

		void DrawRect(float left, float top, float right, float bottom) {
			renderTarget->DrawRectangle(D2D1::Rect(left, top, right, bottom), brush, 3.0f);
		}

		void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
			renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 2.0f);
			renderTarget->DrawLine(D2D1::Point2F(x2, y2), D2D1::Point2F(x3, y3), brush, 2.0f);
			renderTarget->DrawLine(D2D1::Point2F(x3, y3), D2D1::Point2F(x1, y1), brush, 2.0f);
		}

		void FillRect(float left, float top, float right, float bottom) {
			renderTarget->FillRectangle({ left, top, right, bottom }, brush);
		}

		void BasicCircle(float x, float y) {
			renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), 50, 50), brush, 1.0f);
		}

		void BasicRect(float x, float y) {
			renderTarget->DrawRectangle(D2D1::Rect(x - 25, y - 25, x + 25, y + 25), brush, 1.0f);
		}
	};

	int temp = 0;
	int temp2 = 0;

	Graphics graphics;
public:
	mainClass(HWND& windowHandle, GraphicsBase& graphics) : graphics(graphics) {}
	void oneTick() {
		graphics.BeginDraw();
		graphics.ClearScreen(0, 0, 0.7);
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