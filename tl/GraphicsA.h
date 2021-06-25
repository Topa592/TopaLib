#pragma once
#include "tldirect2d.h"
namespace tl {
	namespace graphicsA {
		void drawText(ID2D1RenderTarget* rendertarget, ID2D1Brush* brush
			, const wchar_t* text, const int& length
			, const float& top, const float& left
			, const float& bottom, const float& right
		);
		void drawText(ID2D1RenderTarget* rendertarget, ID2D1Brush* brush
			, const char* text, const int& length
			, const float& top, const float& left
			, const float& bottom, const float& right
		);
	}
}