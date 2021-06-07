#pragma once
#include "sgehelper.h"
namespace tl {
	namespace sge {
		namespace setup {
			//Remember to add functions with tl::sge::create::func();
			void Run();
			//Only necessary if calling Run(); takes too long
			void HideConsole();
		}
		struct Color {
			float r, g, b;
			float a = 1;
			Color() = default;
			Color(float r, float g, float b, float a = 1);
			Color(sge::BasicColor bc, float a = 1);
			Color(unsigned int hexcolor, float a = 1);
		};
		struct Point {
			int x;
			int y;
			Point() = default;
			Point(int x, int y);
		};
		struct Rect {
			int top;
			int left;
			int bottom;
			int right;
			Rect() = default;
			Rect(int top, int left, int bottom, int right);
		};
		enum class Clicktype {
			LDown = 0,
			MDown = 1,
			RDown = 2,
			LUp = 3,
			MUp = 4,
			RUp = 5,
			ScrollDown = 6,
			ScrollUp = 7
		};
		struct Click {
			Clicktype type;
			Point location;
		};
		struct GridClick {
			Rect clickedGridArea;
			int x;
			int y;
			Click click;
		};
		struct ButtonClick {
			Rect buttonArea;
			Click click;
		};
		class Create {
		public:
			//static void KeyboardListener()
			static void Grid(sge::Rect area, int width, int height, void (*Func)(GridClick c));
			static void Button(sge::Rect area, void (*Func)(ButtonClick c));
			static void Func(void (*Func)(void));
			//static void ButtomSpammable(sge::Rect )
			//static void ButtonHold(sge::Rect area, void (*Func)(sge::Point p));
			//static void ButtonToggle(sge::Rect area);
		};
		class Engine {
		public:
			inline static Color Background = { sge::BasicColor::LightBlue, 1 };
			inline static int Tickrate = 50;
			void static shutdown();
		};
		class Graphics {
		public:
			static void setBrush(Color c);
			static void setBackground(Color c);

			static void drawLine(Point p1, Point p2);

			static void drawCircle(Point p, float radius);
			static void drawRect(Rect r);
			static void drawTriangle(Point p1, Point p2, Point p3);

			static void fillRect(Rect r);
			//see more advanced text writing in text.h
			static void drawText(const wchar_t* c, int length, Rect area);
			static void drawText(const char* c, int length, Rect area);
		};
		class Input {
		public:
			static bool ifKeyDown(char c);
			static bool ifKeyUp(char c);
		};
	}
}