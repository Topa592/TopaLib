#pragma once
namespace tl {
	namespace sge {
		struct Color {
			float r = 0, g = 0, b = 0;
			float a = 0;
		};
		struct Point {
			int x;
			int y;
		};
		struct Rect {
			int top;
			int left;
			int bottom;
			int right;
		};
		class Create {
		public:
			static void Grid(sge::Rect area, int width, int height, void (*Func)(sge::Point p, int x, int y));
			static void Button(sge::Rect area, void (*Func)(sge::Point p));
			//static void ButtomSpammable(sge::Rect )
			static void ButtonHold(sge::Rect area, void (*Func)(sge::Point p));
			//static void ButtonToggle(sge::Rect area);
			static sge::Rect Rect(int top, int left, int bottom, int right);
			static sge::Point Point(int x, int y);
			static sge::Color Color(float r, float g, float b, float a);
		};
		class Engine {
		public:
			inline static Color Background = { 0,0,0.7f };
			inline static int Tickrate = 50;
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
			static void drawText(const wchar_t* c, int length, Rect area);
		};
		class Input {
		public:
			static bool ifKeyDown(char c);
			static bool ifKeyUp(char c);
		};
	}
}