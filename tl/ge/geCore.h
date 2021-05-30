#pragma once
#include "core.h"
#include <Windows.h>
#include <vector>
namespace tl {
	namespace gecore {
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void mainLoop();
		void addStaticTick(void (*Func)(void));
		inline static int Tickrate = 50;
		inline static ge::Color BackgroundColor = { 0,0,0.7f };
		void clearScreen(ge::Color c);
		namespace windowproc {
			//void addStatic
		}
	}
}