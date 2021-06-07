#pragma once
#include "game.h"
#include <string>
namespace tl {
	namespace sge {
		enum Fontsize {
			small = 0,
			medium = 1,
			big = 2,
			huge = 3
		};
		struct Font {
			Fontsize size = Fontsize::small;
			Color color;
		};
		class Text {
		public:
			enum Size {
				small = 0,
				medium = 1,
				big = 2,
				huge = 3
			};
			std::wstring text;
			Rect area;
			Color color = sge::BasicColor::Black;
			Size size;
		};
	}
}