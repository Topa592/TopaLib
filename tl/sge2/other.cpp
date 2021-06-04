#include "engine.h"
#include <windowsx.h>
#include <Windows.h>
#include "../Graphics.h"

void tl::sge2::core::Graphics::clearScreen(Color c) {
	tl::graphics::ClearScreen(c.r, c.g, c.b);
}