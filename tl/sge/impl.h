#pragma once
#include "sge.h"
#include <vector>
#include "../Mouse.h"
#include "../WindowProc.h"
namespace tl {
	namespace sge {
		namespace impl {
			LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			struct ClickData {
				bool clicked = false;
				sge::Point location = { 0,0 };
				void reset() {
					clicked = false;
				}
			};
			class Inputs {
			public:
				//more info in game.h Clicktype
				//0 LDown, 1 MDown, 2 RDown, 3 LUp, 4 MUp, 5 RUp
				inline static int mouseDataSize = 6;
				inline static ClickData mouseData[6];
				static void resetInput();
			};
			void mainLoop(int (*Tick)(void));
			struct ButtonData {
				tl::sge::Rect area;
				void (*Func)(sge::ButtonClick c);
			};
			struct GridData {
				tl::sge::Rect area;
				int width;
				int height;
				void (*Func)(sge::GridClick c);
			};
			class Graphics {
			public:
				inline static Color backGroundColor = { 0,0,0.7f };
				static void clearScreen(Color c);
			};
			inline std::vector<ButtonData> buttons;
			inline std::vector<GridData> grids;
			inline bool done = false;
			
			void drawButtons();
			void drawGrids();
			void drawAll();

			void handleMouse();
			void MouseInput(int type, LPARAM lParam);

			auto lParamToSGEPoint(LPARAM lParam)->tl::sge::Point;
		}
	}
}