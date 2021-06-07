#include "Text.h"
#include <string>
#include "Graphics.h"
#include "tldirect2d.h"
template<>
void tl::text::drawText(const std::string& text
	, const int& top, const int& left
	, const int& bottom, const int& right) {
	tl::graphics::drawText(text.c_str(), (UINT32)text.length(), (float)top, (float)left, (float)bottom, (float)right);
}

template<typename Text>
void tl::text::drawText(const Text& text
	, const int& top, const int& left
	, const int& bottom, const int& right) {
	drawText(std::to_string(text), top, left, bottom, right);
}

template<>
void tl::widetext::drawText(const std::wstring& text
	, const int& top, const int& left
	, const int& bottom, const int& right) {
	tl::direct2d::renderTarget->DrawTextW(
		text.c_str(),
		(UINT32)text.size(),
		tl::direct2d::textFormat,
		D2D1::RectF((float)left, (float)top, (float)right, (float)bottom),
		tl::direct2d::brush);
}

template<typename Text>
void tl::widetext::drawText(const Text& text
	, const int& top, const int& left
	, const int& bottom, const int& right) {
	drawText(std::to_wstring(text), top, left, bottom, right);
}