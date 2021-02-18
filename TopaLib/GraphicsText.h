#pragma once
#include "Graphics.h"
#include <string>

class GraphicsText {
private:
	GraphicsBase* base;
public:
	GraphicsText(GraphicsBase* x) : base(x) {}

	void characterToText(const char& t, int x, int y);

	void stringToText(std::string& s, int x, int y);

	void func() {
		base->BasicCircle(10, 10);
	}
};