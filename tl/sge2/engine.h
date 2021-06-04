#pragma once
#include "ph/game.h"
#include <vector>
#include "../Mouse.h"
#include "../WindowProc.h"
namespace tl {
	namespace sge2 {
		namespace core {
			inline std::vector<void (*)(void)> userFunctions;
			void mainLoop(int (*Tick)(void));
			class Engine {
			public:
				inline static bool done = false;
			};
			struct ButtonData {
				Rect area;
				void (*Func)(Point p);
			};
			struct GridData {
				Rect area;
				int width;
				int height;
				void (*Func)(Point p, int x, int y);
			};
			class Graphics {
			public:
				static void clearScreen(Color c);
			};
			class Input {
			public:
				static int InputProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			};

		}
	}
}