#pragma once
#include "game.h"
#include <Windows.h>
//
// Lower level access to windows api's messageloop
// 
// this is meant as just extension to sge for features not supported yet
// but the engine wasn't made in mind of people having access to these features
// so using this is going to require learning about Windows api
// 
// these added functions are first to be called from the engine
//
// things to note is that begindraw + clearscreen happens 
// before any of current tick events happen
//
namespace tl::sge::wa {
	void AddMessageLoop(void(*messageLoop)(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam));
}