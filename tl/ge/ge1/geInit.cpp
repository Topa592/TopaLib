#include "geInit.h"
#include "ge.h"
#include "../geCore.h"
#include "../../tlwindows.h"

void tl::ge::Init(int nShowCmd) {
	HINSTANCE hInstance = GetModuleHandle(0);
	tl::windows::InitDirect2DWindow(hInstance, nShowCmd, tl::gecore::WindowProc, { 0,0,1280,720 }, NULL);
	tl::gecore::addStaticTick(tl::ge::engineTick);
	tl::gecore::mainLoop();
}

