#include "tldirect2d.h"

bool createFactory();
bool createRenderTarget(HWND&);
bool createBrush();

bool tl::direct2d::Init(HWND windowHandle) {
	if (createFactory() == false) return false;
	if (createRenderTarget(windowHandle) == false) return false;
	if (createBrush() == false) return false;

<<<<<<< HEAD
=======
	tl::direct2d::ifInit = true;
>>>>>>> d06e6c294d730edae9143b4e6c28e8974d628b00
	return true;
}

void tl::direct2d::Shutdown() {
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
}


//Helpers

<<<<<<< HEAD
bool createFactory() {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &tl::direct2d::factory);
=======
using namespace tl::direct2d;

bool createFactory() {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
>>>>>>> d06e6c294d730edae9143b4e6c28e8974d628b00
	if (res != S_OK) return false;
	return true;
}

bool createRenderTarget(HWND& windowHandle) {
	RECT rect;
	GetClientRect(windowHandle, &rect);
<<<<<<< HEAD
	HRESULT res = tl::direct2d::factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
		windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&tl::direct2d::renderTarget);
=======
	HRESULT res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
		windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&renderTarget);
>>>>>>> d06e6c294d730edae9143b4e6c28e8974d628b00

	if (res != S_OK) return false;
	return true;
}

bool createBrush() {
<<<<<<< HEAD
	HRESULT res = tl::direct2d::renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &tl::direct2d::brush);
=======
	HRESULT res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
>>>>>>> d06e6c294d730edae9143b4e6c28e8974d628b00
	if (res != S_OK) return false;
	return true;
}