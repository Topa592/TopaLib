#pragma once

namespace tl {
	//for more advanced graphics just use tldirect2d.h for drawing to rendertarget directly
	namespace graphics {
		void setBrush(float r, float g, float b, float a);

		void BeginDraw();
		void EndDraw();

		void ClearScreen(float r, float g, float b);
		void ClearScreen();

		void DrawLine(float x1, float y1, float x2, float y2);

		void DrawCircle(float x, float y, float radius);
		void DrawRect(float left, float top, float right, float bottom);
		void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
		void drawText(const wchar_t* c, const int& length, const float& top, const float& left, const float& bottom, const float& right);
		void drawText(const char* c, const int& length, const float& top, const float& left, const float& bottom, const float& right);

		void FillRect(float left, float top, float right, float bottom);

		void BasicCircle(float x, float y);
		void BasicRect(float x, float y);
	}
}