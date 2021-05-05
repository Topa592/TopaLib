#pragma once

namespace tl {
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

		void FillRect(float left, float top, float right, float bottom);

		void BasicCircle(float x, float y);
		void BasicRect(float x, float y);
	}
}