#pragma once
#include <Windows.h>
namespace tl {
	namespace ge {
		namespace setup {
			void Init(void (*Tick)(void), int nShowCmd);
		}
	}
}