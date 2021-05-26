#include "tldirect2d.h"
#include <cstdlib>

namespace {
	D2D1_SIZE_U newWindowSize;
	bool change = false;

	using namespace tl::direct2d;

	void atExit() {
		if (factory) factory->Release();
		if (renderTarget) renderTarget->Release();
		if (brush) brush->Release();
		if (writeFactory) writeFactory->Release();
		if (textFormat) textFormat->Release();
	}

	bool createFactory() {
		HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
		return (res == S_OK);
	}

	bool createRenderTarget(HWND& windowHandle) {
		RECT rect;
		GetClientRect(windowHandle, &rect);
		HRESULT res = factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
			&renderTarget);
		newWindowSize.width = rect.right;
		newWindowSize.height = rect.bottom;
		return (res == S_OK);
	}

	bool createBrush() {
		HRESULT res = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
		if (res != S_OK) return false;
		return true;
	}

	bool createWriteFactory() {
		HRESULT res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&writeFactory)
		);
		return (res == S_OK);
	}

	bool createTextFormat() {
		HRESULT res = writeFactory->CreateTextFormat(
			L"Consolas",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			11.0f,
			L"en-us",
			&textFormat
		);
		if (res != S_OK) return false;
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		return (res == S_OK);
	}
}

bool tl::direct2d::Init(HWND windowHandle) {
	std::atexit(atExit);
	if (!createFactory()) return false;
	if (!createRenderTarget(windowHandle)) return false;
	if (!createBrush()) return false;
	if (!createWriteFactory()) return false;
	if (!createTextFormat()) return false;

	tl::direct2d::ifInit = true;
	return true;
}

void tl::direct2d::ResizeRenderTarget(HWND windowHandle) {
	if (!tl::direct2d::ifInit) return;
	change = true;
	RECT rect;
	GetClientRect(windowHandle, &rect);
	newWindowSize.width = rect.right;
	newWindowSize.height = rect.bottom;
}

void tl::direct2d::ResizeRenderTarget(int width, int height) {
	change = true;
	newWindowSize.width = width;
	newWindowSize.height = height;
}

void tl::direct2d::updateChanges() {
	if (!change) return;
	renderTarget->Resize(newWindowSize);
}