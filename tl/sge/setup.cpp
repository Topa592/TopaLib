#include "../ph/sge/setup.h"
#include "../tlwindows.h"
#include "sge.h"

void tl::sge::setup::Init(int(*Tick)(void), _In_ int nShowCmd) {
	HINSTANCE hInstance = GetModuleHandle(0);
	tl::windows::InitDirect2DWindow(hInstance, nShowCmd, tl::sge::e::WindowProc);
	tl::sge::e::mainLoop(Tick);
}