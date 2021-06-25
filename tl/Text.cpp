#include "Text.h"
#include <string>
#include "Graphics.h"
#include "tldirect2d.h"
#include <type_traits>

void tl::text::drawText(const std::string& text, const int& top, const int& left, const int& bottom, const int& right) {
	tl::graphics::drawText(text.c_str(), (UINT32)text.length(), (float)top, (float)left, (float)bottom, (float)right);
}

void tl::text::drawText(const std::wstring& wtext, const int& top, const int& left, const int& bottom, const int& right) {
	tl::direct2d::renderTarget->DrawText(
		wtext.c_str(),
		(UINT32)wtext.size(),
		tl::direct2d::textFormat,
		D2D1::RectF((float)left, (float)top, (float)right, (float)bottom),
		tl::direct2d::brush);
}
