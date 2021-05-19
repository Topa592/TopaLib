#pragma once
#include <Windows.h>
#include "Datatypes.h"
namespace tl {
	namespace eventQue {
		void run();
		void clear();
		void deleteFunctions();
		namespace mouse {
			void addFuncOnLButtonDown(void(*func)(tl::datatypes::Point point));
		}
	}
}