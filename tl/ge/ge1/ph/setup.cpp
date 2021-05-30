#include "setup.h"
#include "../geInit.h"
void tl::ge::setup::Init(void(*Tick)(void), int nShowCmd) {
	tl::ge::addStaticTick(Tick);
	tl::ge::Init(nShowCmd);
}