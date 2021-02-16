#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#pragma comment(lib, "d2d1.lib")

class Graphics
{
private:
	ID2D1Factory* factory;
	IDWriteFactory* writeFactory; //TODO text
	IDWriteTextFormat* textFormat;
public:
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);
};