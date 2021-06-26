#pragma once
#include "sge.h"
#include <vector>
#include <Windows.h>
#include <memory>
namespace tl::sge::e {
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	struct ClickData {
		bool clicked = false;
		Click click;
		void reset() {
			clicked = false;
		}
		ClickData(Clicktype c) {
			click.type = c;
		}
	};
	struct KeyData {
		bool down = false;
	};
	namespace Inputs {
		namespace mouse {
			void processActions();
			inline const int size = 8;
			//more info in game.h Clicktype
			inline ClickData data[8] = { 
				Clicktype::LDown,
				Clicktype::MDown,
				Clicktype::RDown,
				Clicktype::LUp,
				Clicktype::MUp,
				Clicktype::RUp,
				Clicktype::ScrollDown,
				Clicktype::ScrollUp
			};
			void Input(int type, LPARAM lParam);
			void Scroll(int type, LPARAM lParam);
		}
		namespace Keyboard {
			//more info in game.h
			inline const int size = 256;
			inline KeyData keyboardData[256];
		}
		
		void handleInput();
		void resetInput();
	}
	void mainLoop();
	
	namespace Graphics {
		inline Color backGroundColor = { 0,0,0.7f };
		void clearScreen(Color c);
	}
	namespace functions {
		void addStatic(void (*Func)(void));
		void runAll();
	}
	namespace mouseListeners {
		void addStatic(void (*Func)(tl::sge::Click c));
		void runAll(const Click& click);
	}
	namespace Mouse {
		void update(const tl::sge::Clicktype& c, const LPARAM& lParam);
		tl::sge::Click getLatestClick(const tl::sge::Clicktype c);
	}
	inline bool done = false;
	//never use for scrolling since scrolling input works differently
	void MouseInput(const int& type, LPARAM lParam);
	void MouseScroll(const WPARAM& wParam, const LPARAM& lParam);

	auto getClientPos()->tl::sge::Point;
	auto lParamToSGEPoint(LPARAM lParam)->tl::sge::Point;
	//scrolling has slightly different way to get position to be like from mouse
	auto scrollToSGEPoint(LPARAM lParam)->tl::sge::Point;
}