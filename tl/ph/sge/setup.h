#pragma once
#include <Windows.h>

namespace tl {
	namespace sge {
		namespace setup {
			void Init(int (*Tick)(void), _In_ int nShowCmd);
		}
	}
}