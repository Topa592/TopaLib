#include "sge.h"
#include <Windows.h>
#include "../Graphics.h"
#include "../tldirect2d.h"
#include <dwrite.h>
using namespace tl;

void tl::sge::Graphics::setBrush(Color c) {
	tl::graphics::setBrush(c.r, c.g, c.b, c.a);
}

void tl::sge::Graphics::setBackground(Color c) {
	e::Graphics::backGroundColor = c;
}

void tl::sge::Graphics::drawLine(Point p1, Point p2) {
	tl::graphics::DrawLine((float)p1.x, (float)p1.y, (float)p2.x, (float)p2.y);
}

void tl::sge::Graphics::drawCircle(Point p, float radius) {
	tl::graphics::DrawCircle((float)p.x, (float)p.y, radius);
}

void tl::sge::Graphics::drawRect(Rect r) {
	tl::graphics::DrawRect((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
}

void tl::sge::Graphics::drawTriangle(Point p1, Point p2, Point p3) {
	tl::graphics::DrawTriangle((float)p1.x, (float)p1.y, (float)p2.x, (float)p2.y
		, (float)p3.x, (float)p3.y);
}

void tl::sge::Graphics::fillRect(Rect r) {
	tl::graphics::FillRect((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
}

void tl::sge::Graphics::drawText(const wchar_t* c, int length, Rect r) {
	tl::graphics::drawText(c, length, (float)r.top, (float)r.left, (float)r.bottom, (float)r.right);
}

void tl::sge::Graphics::drawText(const char* c, int length, Rect r) {
	tl::graphics::drawText(c, length, (float)r.top, (float)r.left, (float)r.bottom, (float)r.right);
}

void tl::sge::Create::Grid(sge::Rect area, int width, int height, void(*Func)(GridClick c)) {
	e::GridData temp = { area, width, height, Func };
	e::grids.push_back(temp);
}

void tl::sge::Create::Button(sge::Rect area, void(*Func)(ButtonClick c)) {
	e::ButtonData temp = { area, Func };
	e::buttons.push_back(temp);
}

void tl::sge::Engine::shutdown() {
	e::done = true;
}

sge::Rect tl::sge::Create::Rect(int top, int left, int bottom, int right) {
	return { top, left, bottom, right };
}

sge::Point tl::sge::Create::Point(int x, int y) {
	return { x, y };
}

sge::Color tl::sge::Create::Color(float r, float g, float b, float a) {
	return { r,g,b,a };
}

bool tl::sge::Input::ifKeyDown(char c) {
	return false;
}

bool tl::sge::Input::ifKeyUp(char c) {
	return false;
}