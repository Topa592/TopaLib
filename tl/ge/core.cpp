#include "core.h"

#include "core.h"
#include "geCore.h"
#include <Windows.h>
#include "../Graphics.h"
#include "../tldirect2d.h"
#include <dwrite.h>
#include <string>
using namespace tl;

void tl::ge::Graphics::setBrush(Color c) {
	tl::graphics::setBrush(c.r, c.g, c.b, c.a);
}

void tl::ge::Graphics::setBackground(Color c) {
	gecore::BackgroundColor = c;
}

void tl::ge::Graphics::drawLine(Point p1, Point p2) {
	tl::graphics::DrawLine((float)p1.x, (float)p1.y, (float)p2.x, (float)p2.y);
}

void tl::ge::Graphics::drawCircle(Point p, float radius) {
	tl::graphics::DrawCircle((float)p.x, (float)p.y, radius);
}

void tl::ge::Graphics::drawRect(Rect r) {
	tl::graphics::DrawRect((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
}

void tl::ge::Graphics::drawTriangle(Point p1, Point p2, Point p3) {
	tl::graphics::DrawTriangle((float)p1.x, (float)p1.y, (float)p2.x, (float)p2.y
		, (float)p3.x, (float)p3.y);
}

void tl::ge::Graphics::fillRect(Rect r) {
	tl::graphics::FillRect((float)r.left, (float)r.top, (float)r.right, (float)r.bottom);
}

void tl::ge::Graphics::drawText(const wchar_t* c, int length, Rect r) {
	tl::graphics::drawText(c, length, (float)r.top, (float)r.left, (float)r.bottom, (float)r.right);
}

void tl::ge::Graphics::drawText(const char* c, int length, Rect r) {
	tl::graphics::drawText(c, length, (float)r.top, (float)r.left, (float)r.bottom, (float)r.right);
}

void tl::ge::Graphics::drawText(Text t, Rect area) {
	
}

ge::Rect tl::ge::Create::Rect(int top, int left, int bottom, int right) {
	return { top, left, bottom, right };
}

ge::Point tl::ge::Create::Point(int x, int y) {
	return { x, y };
}

ge::Color tl::ge::Create::Color(float r, float g, float b, float a) {
	return { r,g,b,a };
}

bool tl::ge::Input::ifKeyDown(char c) {
	return false;
}

bool tl::ge::Input::ifKeyUp(char c) {
	return false;
}

class tl::ge::Text::Impl {
private:

public:
	std::wstring text = L"";
};

tl::ge::Text::Text() {
	pimpl = new Impl();
}

tl::ge::Text::~Text() {
	delete pimpl;
}

void tl::ge::Text::operator=(int x) {
	pimpl->text = std::to_wstring(x);
}

void tl::ge::Text::operator=(Text x) {
	pimpl->text = x.pimpl->text;
}

void tl::ge::Text::setText(const char* c, int length) {
	pimpl->text.resize(length);
	for (int i = 0; i < length; i++) {
		pimpl->text[i] = c[i];
	}
}

void tl::ge::Text::setText(const wchar_t* c, int length) {
	pimpl->text.reserve(length);
	for (int i = 0; i < length; i++) {
		pimpl->text[i] = c[i];
	}
}
