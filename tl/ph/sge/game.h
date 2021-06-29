#pragma once
#include "old.h"
#include "enums.h"
#include "utility.h"
namespace tl {
	namespace sge {
		namespace setup {
			//Remember to add functions with tl::sge::create::func();
			void Run();
			//Will init at run but some features outside sge are not usable without initializing such as WIN32 api features
			void Init();
		}
		struct Color {
			float r = 0, g = 0, b = 0;
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
		struct Brush {
			Color color;
			float thickness;
			Brush() = default;
			Brush(Color color, float thickness);
		};
		enum class Clicktype {
			LDown = 0,
			MDown = 1,
			RDown = 2,
			LUp = 3,
			MUp = 4,
			RUp = 5,
			ScrollDown = 6,
			ScrollUp = 7,
			//often used for mouse moving
			None = 8
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
		/*struct ButtonHold {
			Rect buttonArea;
			Point location;
			//will return once up when mouse is lifted or moved out of area
			bool down;
		};*/
		namespace Create {
			void MouseListener(void (*Func)(Click c));
			//void MouseListener(void (*Func)(Click c), sge::Rect area); //TODO make area based listener

			void Grid(sge::Rect area, int width, int height, void (*Func)(GridClick c));
			void Button(sge::Rect area, void (*Func)(ButtonClick c));
			//runs every tick
			void Func(void (*Func)(void));
			//TODO add simpler just bool/function call buttons since that's most needed
			//like for HoldButton having all different types of inputs is going to be confusing
			//to use but just having it call everytime it is holded is far simpler for usercode
			
			//TODO add proper customization to buttons and grids
			
			//void ButtomSpammable(sge::Rect )
			//void HoldButton(sge::Rect area, void (*Func)(ButtonHold p));
			//void ButtonToggle(sge::Rect area);
		};
		namespace Engine {
			inline Color Background = { sge::BasicColor::LightBlue, 1 };
			inline int Tickrate = 50;
			void shutdown();
		};
		namespace Graphics {
			void setBrush(Color c);
			void setBackground(Color c);

			void drawLine(Point p1, Point p2);

			void drawCircle(Point p, float radius);
			void drawRect(Rect r);
			void drawTriangle(Point p1, Point p2, Point p3);

			void fillRect(Rect r);
			//see more advanced text writing in text.h
			void drawText(const wchar_t* c, int length, Rect area);
			void drawText(const char* c, int length, Rect area);
		};
		class Canvas {
		private:
			class Impl; Impl* impl;
			Color background = Color(sge::BasicColor::White, 0);
			Brush brush = Brush(Color(sge::BasicColor::Black), 1);
		public:
			Canvas();
			~Canvas();
			//offset from point topleft
			Rect drawArea = { 0,0,100,100 };
			Point topLeft = { 150,150 };
			//used to move current drawing area
			Point offset = { 0,0 };

			void beginDraw();
			void endDraw();

			void setBrush(Brush brush);
			//set a (alpha) to 0 to not have background color
			void setBackground(Color c);

			void drawLine(Point p1, Point p2);

			void drawCircle(Point p, float heigth, float width);
			void drawRect(Rect r);
			void drawTriangle(Point p1, Point p2, Point p3);

			void fillRect(Rect r);
			//see more advanced text writing in text.h
			void drawText(const wchar_t* c, int length, Rect area);
			void drawText(const char* c, int length, Rect area);
		};
	}
}