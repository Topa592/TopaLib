#pragma once
#include "../game.h"
#include <vector>
#include "../../Mouse.h"
#include "../../WindowProc.h"
namespace tl {
	namespace sge {
		namespace impl {
			
			struct ClickData {
				bool clicked = false;
				sge::Point location = { 0,0 };
				void reset() {
					clicked = false;
				}
			};
			class Inputs {
			public:
				//0 LDown, 1 MDown, 2 RDown, 3 LUp, 4 MUp, 5 RUp
				inline static ClickData mouseData[6];
				static void resetInput();
			};
			void mainLoop(int (*Tick)(void));
			struct ButtonData {
				tl::sge::Rect area;
				void (*Func)(tl::sge::Point p);
			};
			class Graphics {
			public:
				inline static Color backGroundColor = { 0,0,0.7f };
				static void clearScreen(Color c);
			};
			inline std::vector<ButtonData> buttons;

			void drawButtons();

			void handleLButtonDown();
			void LButtonDown(LPARAM lParam);

			auto lParamToSGEPoint(LPARAM lParam)->tl::sge::Point;
		}
	}
}