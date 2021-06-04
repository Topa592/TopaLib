#pragma once
namespace tl {
	namespace sge2 {
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
		enum InputType {
			a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,
			i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,
			LB,MB,RB
		};
		class Create {
		public:
			static Rect Rect(int top, int left, int bottom, int right);
			static Point Point(int x, int y);
			static Color Color(float r, float g, float b, float a);
		};
		class Engine {
		public:
			inline static Color backgroundColor = { 0,0,0.7f };
			inline static int tickrate = 50;
			static void close();
		};
		class Graphics {
		public:
			static void setBrush(Color c);

			static void drawLine(Point p1, Point p2);

			static void drawCircle(Point p, float radius);
			static void drawRect(Rect r);
			static void drawTriangle(Point p1, Point p2, Point p3);

			static void fillRect(Rect r);
			static void drawText(const wchar_t* c, int length, Rect area);
			static void drawText(const char* c, int length, Rect area);
		};
	}
}