#include "Graphics.h"
#include "tldirect2d.h"
#include <cstdlib>

using tl::direct2d::brush;
using tl::direct2d::renderTarget;

void tl::graphics::setBrush(float r, float g, float b, float a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
}

void tl::graphics::BeginDraw() {
	if (tl::direct2d::ifInit == false) std::exit(EXIT_FAILURE);
	renderTarget->BeginDraw();
}

void tl::graphics::EndDraw() {
	renderTarget->EndDraw();
}

void tl::graphics::ClearScreen(float r, float g, float b) {
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void tl::graphics::ClearScreen() {
	renderTarget->Clear();
}

void tl::graphics::DrawLine(float x1, float y1, float x2, float y2) {
	renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 1.0f);
}

void tl::graphics::DrawCircle(float x, float y, float radius) {
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

void tl::graphics::DrawRect(float left, float top, float right, float bottom) {
	renderTarget->DrawRectangle(D2D1::Rect(left, top, right, bottom), brush, 3.0f);
}

void tl::graphics::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	renderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 2.0f);
	renderTarget->DrawLine(D2D1::Point2F(x2, y2), D2D1::Point2F(x3, y3), brush, 2.0f);
	renderTarget->DrawLine(D2D1::Point2F(x3, y3), D2D1::Point2F(x1, y1), brush, 2.0f);
}

void tl::graphics::FillRect(float left, float top, float right, float bottom) {
	renderTarget->FillRectangle({ left, top, right, bottom }, brush);
}

void tl::graphics::BasicCircle(float x, float y) {
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), 50, 50), brush, 1.0f);
}

void tl::graphics::BasicRect(float x, float y) {
	renderTarget->DrawRectangle(D2D1::Rect(x - 25, y - 25, x + 25, y + 25), brush, 1.0f);
}