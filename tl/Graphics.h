#pragma once

namespace tl {
	class graphics {
	public:
		static void setBrush(float r, float g, float b, float a);

		static void BeginDraw();
		static void EndDraw();

		static void ClearScreen(float r, float g, float b);
		static void ClearScreen();

		static void DrawLine(float x1, float y1, float x2, float y2);

		static void DrawCircle(float x, float y, float radius);
		static void DrawRect(float left, float top, float right, float bottom);
		static void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
		static void drawText(const wchar_t* c, int length, float top, float left, float bottom, float right);
		static void drawText(const char* c, int length, float top, float left, float bottom, float right);

		static void FillRect(float left, float top, float right, float bottom);

		static void BasicCircle(float x, float y);
		static void BasicRect(float x, float y);
	};
}