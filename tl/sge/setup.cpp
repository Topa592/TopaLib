#include "setup.h"
#include "../tlwindows.h"
#include "impl/impl.h"

void tl::sge::setup::Init(int(*Tick)(void), _In_ int nShowCmd) {
	HINSTANCE hInstance = GetModuleHandle(0);
	tl::windows::InitDirect2DWindow(hInstance, nShowCmd, WindowProc);
	tl::sge::impl::mainLoop(Tick);
}
