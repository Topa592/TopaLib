#include "game.h"
#include "../engine.h"
#include <Windows.h>
#include "../../Graphics.h"
#include "../../tldirect2d.h"
#include <dwrite.h>
using namespace tl;

void tl::sge2::Graphics::setBrush(Color c) {
	tl::graphics::setBrush(c.r, c.g, c.b, c.a);
}

void tl::sge2::Graphics::drawLine(Point p1, Point p2) {
	tl::graphics::DrawLine((float)p1.x, (float)p1.y, (float)p2.x, (float)p2.y);
}

void tl::sge2::Graphics::drawCircle(Point p, float radius) {
	tl::graphics::DrawCircle((float)p.x, (float)p.y, radius);
}

void tl::sge2::Graphics::drawRect(Rect r) {
	tl::graphics::DrawRect((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
}

void tl::sge2::Graphics::drawTriangle(Point p1, Point p2, Point p3) {
	tl::graphics::DrawTriangle((float)p1.x, (float)p1.y, (float)p2.x, (float)p2.y
		, (float)p3.x, (float)p3.y);
}

void tl::sge2::Graphics::fillRect(Rect r) {
	tl::graphics::FillRect((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
}

void tl::sge2::Graphics::drawText(const wchar_t* c, int length, Rect r) {
	tl::graphics::drawText(c, length, (float)r.top, (float)r.left, (float)r.bottom, (float)r.right);
}

void tl::sge2::Graphics::drawText(const char* c, int length, Rect r) {
	tl::graphics::drawText(c, length, (float)r.top, (float)r.left, (float)r.bottom, (float)r.right);
}

sge2::Rect tl::sge2::Create::Rect(int top, int left, int bottom, int right) {
	return { top, left, bottom, right };
}

sge2::Point tl::sge2::Create::Point(int x, int y) {
	return { x, y };
}

sge2::Color tl::sge2::Create::Color(float r, float g, float b, float a) {
	return { r,g,b,a };
}

void sge2::Engine::close() {
	core::Engine::done = true;
}