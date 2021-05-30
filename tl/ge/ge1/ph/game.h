#pragma once
#include "../../core.h"
namespace tl {
	namespace ge {
		class Object {
		private:
			void (*Func)(void);
		public:
			Object(void (*Func)(void)): Func(Func) {}
			ge::Point location;
			
		};
	}
}