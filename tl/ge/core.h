#pragma once
namespace tl {
	namespace ge {
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
		class Text {
		private:
			class Impl; Impl* pimpl;
		public:
			Text();
			~Text();
			void operator=(int x);
			void operator=(Text x);
			void setText(const char* c, int length);
			void setText(const wchar_t* c, int length);

		};
		class Engine {
		public:
			inline static Color Background = { 0,0,0.7f };
			inline static int Tickrate = 50;
		};
		class Create {
		public:
			static ge::Rect Rect(int top, int left, int bottom, int right);
			static ge::Point Point(int x, int y);
			static ge::Color Color(float r, float g, float b, float a);
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
			static void drawText(const char* c, int length, Rect area);
			static void drawText(Text t, Rect area);
		};
		class Input {
		public:
			static bool ifKeyDown(char c);
			static bool ifKeyUp(char c);
		};
	}
}