#include "sge.h"
#include <Windows.h>
#include "../Graphics.h"
#include "../tldirect2d.h"
#include "../tlwindows.h"
#include <dwrite.h>
using namespace tl;

void tl::sge::setup::Run() {
	setup::HideConsole();
	tl::windows::InitDirect2DWindow(tl::sge::e::WindowProc);
	e::mainLoop();
}

void tl::sge::setup::HideConsole() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}

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

void tl::sge::Create::Func(void(*Func)(void)) {
	e::funcs.push_back({ Func });
}

void tl::sge::Engine::shutdown() {
	e::done = true;
}

bool tl::sge::Input::ifKeyDown(char c) {
	return false;
}

bool tl::sge::Input::ifKeyUp(char c) {
	return false;
}

tl::sge::Color::Color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

tl::sge::Color::Color(sge::BasicColor bc, float a) {
	const unsigned int hexcolor = static_cast<unsigned int>(bc);
	static const uint32_t sc_redShift = 16;
	static const uint32_t sc_greenShift = 8;
	static const uint32_t sc_blueShift = 0;
	static const uint32_t sc_redMask = 0xff << sc_redShift;
	static const uint32_t sc_greenMask = 0xff << sc_greenShift;
	static const uint32_t sc_blueMask = 0xff << sc_blueShift;
	this->r = static_cast<FLOAT>((hexcolor & sc_redMask) >> sc_redShift) / 255.f;
	this->g = static_cast<FLOAT>((hexcolor & sc_greenMask) >> sc_greenShift) / 255.f;
	this->b = static_cast<FLOAT>((hexcolor & sc_blueMask) >> sc_blueShift) / 255.f;
	this->a = a;
}

tl::sge::Color::Color(unsigned int hexcolor, float a) {
	static const uint32_t sc_redShift = 16;
	static const uint32_t sc_greenShift = 8;
	static const uint32_t sc_blueShift = 0;
	static const uint32_t sc_redMask = 0xff << sc_redShift;
	static const uint32_t sc_greenMask = 0xff << sc_greenShift;
	static const uint32_t sc_blueMask = 0xff << sc_blueShift;
	this->r = static_cast<FLOAT>((hexcolor & sc_redMask) >> sc_redShift) / 255.f;
	this->g = static_cast<FLOAT>((hexcolor & sc_greenMask) >> sc_greenShift) / 255.f;
	this->b = static_cast<FLOAT>((hexcolor & sc_blueMask) >> sc_blueShift) / 255.f;
	this->a = a;
}

tl::sge::Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

tl::sge::Rect::Rect(int top, int left, int bottom, int right) {
	this->top = top;
	this->left = left;
	this->bottom = bottom;
	this->right = right;
}
