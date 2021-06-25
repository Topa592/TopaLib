#include "GraphicsA.h"
void tl::graphicsA::drawText(ID2D1RenderTarget* rendertarget, ID2D1Brush* brush, const wchar_t* c, const int& length, const float& top, const float& left, const float& bottom, const float& right) {
	rendertarget->DrawTextW(
		c,
		length,
		tl::direct2d::textFormat,
		D2D1::RectF(left, top, right, bottom),
		brush);
}

void tl::graphicsA::drawText(ID2D1RenderTarget* rendertarget, ID2D1Brush* brush, const char* c, const int& length, const float& top, const float& left, const float& bottom, const float& right) {
	wchar_t* text = new wchar_t[length];
	for (int i = 0; i < length; i++) {
		text[i] = c[i];
	}
	rendertarget->DrawTextW(
		text,
		length,
		tl::direct2d::textFormat,
		D2D1::RectF(left, top, right, bottom),
		brush);
	delete[] text;
}