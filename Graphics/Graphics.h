#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#pragma comment(lib, "d2d1.lib")

class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget; //TODO layers
	ID2D1SolidColorBrush* brush;
	IDWriteFactory* writeFactory; //TODO text
	IDWriteTextFormat* textFormat;
public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	void setBrush(float r, float g, float b, float a);

	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void ClearScreen();

	void DrawCircle(float x, float y, float radius);
	void DrawRect(float left, float top, float right, float bottom);
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	void BasicCircle(float x, float y);
	void BasicRect(float x, float y);
};

class GraphicShapes {
private:
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
public:
	GraphicShapes(Graphics& graphics);
};