#pragma once
#include "sge.h"
#include <vector>
#include <Windows.h>
namespace tl {
	namespace sge {
		namespace e {
			LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			struct ClickData {
				bool clicked = false;
				sge::Point location = { 0,0 };
				void reset() {
					clicked = false;
				}
			};
			struct KeyData {
				bool down = false;
			};
			namespace Inputs {
				class Mouse {
				public:
					//more info in game.h Clicktype
					//0 LDown, 1 MDown, 2 RDown, 3 LUp, 4 MUp, 5 RUp, 6 ScrollDown, 7 ScrollUp
					inline const static int size = 8;
					inline static ClickData data[8];
				};
				class Keyboard {
				public:
					//more info in game.h
					inline const static int size = 256;
					inline static KeyData keyboardData[256];
				};
				
				
				
				static void resetInput();
			}
			void mainLoop();
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
			struct FuncData {
				void (*Func)(void);
			};
			class Graphics {
			public:
				inline static Color backGroundColor = { 0,0,0.7f };
				static void clearScreen(Color c);
			};
			inline std::vector<ButtonData> buttons;
			inline std::vector<GridData> grids;
			inline std::vector<FuncData> funcs;
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