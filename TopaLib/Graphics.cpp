#include "Graphics.h"

Graphics::Graphics() {
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
	writeFactory = NULL;
	textFormat = NULL;
}

Graphics::~Graphics() {
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
	if (writeFactory) writeFactory->Release();
	if (textFormat) textFormat->Release();
}

bool Graphics::Init(HWND windowHandle) {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK) return false;

	//DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory));

	res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;
	return true;
}

void Graphics::setBrush(float r, float g, float b, float a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
}

void Graphics::ClearScreen(float r, float g, float b) {
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::ClearScreen() {
	renderTarget->Clear();
}

void Graphics::DrawCircle(float x, float y, float radius) {
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

void Graphics::DrawRect(float left, float top, float right, float bottom) {
	renderTarget->DrawRectangle(D2D1::Rect(left, top, right, bottom), brush, 3.0f);
}

void Graphics::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 2.0f);
	renderTarget->DrawLine(D2D1::Point2F(x2, y2), D2D1::Point2F(x3, y3), brush, 2.0f);
	renderTarget->DrawLine(D2D1::Point2F(x3, y3), D2D1::Point2F(x1, y1), brush, 2.0f);
}

void Graphics::BasicCircle(float x, float y) {
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), 50, 50), brush, 1.0f);
}

void Graphics::BasicRect(float x, float y) {
	renderTarget->DrawRectangle(D2D1::Rect(x - 25, y - 25, x + 25, y + 25), brush, 1.0f);
}