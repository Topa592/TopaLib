#pragma once
#include "sge.h"
namespace tl {
	namespace sge {
		namespace e {
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
			struct ButtonHoldData {
				tl::sge::Rect area;
				void (*Func)(sge::ButtonHold c);
			};
		}
	}
}