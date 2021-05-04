#include "tldirect2d.h"
#include <cstdlib>

void atExit();
bool createFactory();
bool createRenderTarget(HWND&);
bool createBrush();

bool tl::direct2d::Init(HWND windowHandle) {
	if (createFactory() == false) return false;
	if (createRenderTarget(windowHandle) == false) return false;
	if (createBrush() == false) return false;

	tl::direct2d::ifInit = true;
	std::atexit(atExit);
	return true;
}

void tl::direct2d::ResizeRenderTarget(HWND windowHandle) {
	RECT rect;
	GetClientRect(windowHandle, &rect);
	renderTarget->Resize(D2D1::SizeU(rect.right, rect.bottom));
}

//Helpers

using namespace tl::direct2d;

void atExit() {
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
}

bool createFactory() {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return false;
	return true;
}

bool createRenderTarget(HWND& windowHandle) {
	RECT rect;
	GetClientRect(windowHandle, &rect);
	HRESULT res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
		windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);

	if (res != S_OK) return false;
	return true;
}

bool createBrush() {
	HRESULT res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;
	return true;
}