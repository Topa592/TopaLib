#pragma once
#include "game.h"
#include <string>
namespace tl {
	namespace sge {
		enum class Fontsize {
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
			enum class Size {
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