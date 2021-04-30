#include "tldirect2d.h"

bool createFactory();
bool createRenderTarget(HWND&);
bool createBrush();

bool tl::direct2d::Init(HWND windowHandle) {
	if (createFactory() == false) return false;
	if (createRenderTarget(windowHandle) == false) return false;
	if (createBrush() == false) return false;

	return true;
}

void tl::direct2d::Shutdown() {
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
}


//Helpers

bool createFactory() {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &tl::direct2d::factory);
	if (res != S_OK) return false;
	return true;
}

bool createRenderTarget(HWND& windowHandle) {
	RECT rect;
	GetClientRect(windowHandle, &rect);
	HRESULT res = tl::direct2d::factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
		windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&tl::direct2d::renderTarget);

	if (res != S_OK) return false;
	return true;
}

bool createBrush() {
	HRESULT res = tl::direct2d::renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &tl::direct2d::brush);
	if (res != S_OK) return false;
	return true;
}