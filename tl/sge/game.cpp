#include "game_in.h"
#include "sge.h"
#include <Windows.h>
#include "../Graphics.h"
#include "../tldirect2d.h"
#include "../tlwindows.h"
#include <dwrite.h>
#include <cstdlib>
using namespace tl;

namespace impl {
	namespace {
		bool ifNotInit = true;
	}
}

void tl::sge::setup::Run() {
	setup::Init();
	e::mainLoop();
}

void tl::sge::setup::Init() {
	if (impl::ifNotInit) {
		impl::ifNotInit = false;
		tl::windows::HideConsole();
		tl::windows::InitDirect2DWindow(tl::sge::e::WindowProc);
	}
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

void tl::sge::Create::MouseListener(void(*Func)(Click c)) {
	e::mouseListeners::addStatic(Func);
}

#include "buttons.h"
void tl::sge::Create::Grid(sge::Rect area, int width, int height, void(*Func)(GridClick c)) {
	e::GridData temp = { area, width, height, Func };
	e::CreateStaticGrid(temp);
}

void tl::sge::Create::Button(sge::Rect area, void(*Func)(ButtonClick c)) {
	e::ButtonData temp = { area, Func };
	e::CreateStaticButton(temp);
}

void tl::sge::Create::Func(void(*Func)(void)) {
	e::functions::addStatic(Func);
}

void tl::sge::Engine::shutdown() {
	e::done = true;
}

tl::sge::Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

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

tl::sge::Point::Point(int x, int y) : x(x), y(y) {}

tl::sge::Rect::Rect(int top, int left, int bottom, int right) : top(top), left(left), bottom(bottom), right(right) {}

tl::sge::Brush::Brush(Color color, float thickness) {
	this->color = color;
	this->thickness = thickness;
}

class tl::sge::Canvas::Impl {
public:
	D2D1_RECT_F area = D2D1::RectF();
	ID2D1SolidColorBrush* brush = NULL;
	bool changed = true;
	Impl() {
		
	}
	~Impl() {
		if (brush) brush->Release();
	}
	void setArea(sge::Rect drawArea) {
		area = this->d2d(drawArea);
	}
	void setoffset(Point& p, const Point& offset) {
		p.x += offset.x;
		p.y += offset.y;
	}
	void setoffset(Rect& r, const Point& offset) {
		r.left += offset.x;
		r.right += offset.x;
		r.top += offset.y;
		r.bottom += offset.y;
	}
	D2D1_POINT_2F d2d(const Point& p) {
		return D2D1::Point2F((float)p.x, (float)p.y);
	}
	D2D1_RECT_F d2d(const Rect& r) {
		return D2D1::RectF((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
	}
};

tl::sge::Canvas::Canvas() : impl(new Impl) {}

tl::sge::Canvas::~Canvas() {
	delete impl;
}

void tl::sge::Canvas::beginDraw() {
	static bool firstTime = true;
	if (firstTime) {
		HRESULT res = tl::direct2d::renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &impl->brush);
		if (res != S_OK) std::exit(EXIT_SUCCESS);
		firstTime = false;
	}
	impl->setArea(this->drawArea);
	ID2D1RenderTarget* r = tl::direct2d::renderTarget;
	r->PushAxisAlignedClip(&impl->area, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	const Color& c = this->background;
	if (c.a != 0) r->Clear(D2D1::ColorF(c.r, c.g, c.b));
	if (impl->changed) {
		const Color& c = this->brush.color;
		impl->brush->SetColor(D2D1::ColorF(c.r, c.g, c.b, c.a));
		impl->changed = false;
	}
}

void tl::sge::Canvas::endDraw() {
	tl::direct2d::renderTarget->PopAxisAlignedClip();
}

void tl::sge::Canvas::setBrush(Brush b) {
	this->brush = b;
	impl->changed = true;
}

void tl::sge::Canvas::setBackground(Color c) {
	this->background = c;
}

void tl::sge::Canvas::drawLine(Point p1, Point p2) {
	auto& r = tl::direct2d::renderTarget;
	impl->setoffset(p1, offset);
	impl->setoffset(p2, offset);
	r->DrawLine(impl->d2d(p1), impl->d2d(p2), impl->brush, this->brush.thickness);
}

void tl::sge::Canvas::drawCircle(Point p, float heigth, float width) {
	auto& r = tl::direct2d::renderTarget;
	impl->setoffset(p, offset);
	r->DrawEllipse(D2D1::Ellipse(impl->d2d(p), width, heigth), impl->brush, this->brush.thickness);
}

void tl::sge::Canvas::drawRect(Rect rect) {
	auto& r = tl::direct2d::renderTarget;
	impl->setoffset(rect, offset);
	r->DrawRectangle(impl->d2d(rect), impl->brush, this->brush.thickness);
}

void tl::sge::Canvas::drawTriangle(Point p1, Point p2, Point p3) {
	this->drawLine(p3, p1);
	this->drawLine(p1, p2);
	this->drawLine(p2, p3);
}

void tl::sge::Canvas::fillRect(Rect rect) {
	auto& r = tl::direct2d::renderTarget;
	impl->setoffset(rect, offset);
	r->FillRectangle(impl->d2d(rect), impl->brush);
}

#include "../GraphicsA.h"

void tl::sge::Canvas::drawText(const wchar_t* c, int length, Rect area) {
	impl->setoffset(area, this->offset);
	tl::graphicsA::drawText(tl::direct2d::renderTarget, impl->brush, c, length
		, (float)area.top, (float)area.left, (float)area.bottom, (float)area.right);
}

void tl::sge::Canvas::drawText(const char* c, int length, Rect area) {
	impl->setoffset(area, this->offset);
	tl::graphicsA::drawText(tl::direct2d::renderTarget, impl->brush, c, length
		, (float)area.top, (float)area.left, (float)area.bottom, (float)area.right);
}