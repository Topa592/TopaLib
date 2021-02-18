#include "Base.h"

GraphicsBase::GraphicsBase() {
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
	writeFactory = NULL;
	textFormat = NULL;
}

GraphicsBase::~GraphicsBase() {
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
	if (brush) brush->Release();
	if (writeFactory) writeFactory->Release();
	if (textFormat) textFormat->Release();
}

bool GraphicsBase::Init(HWND windowHandle) {
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