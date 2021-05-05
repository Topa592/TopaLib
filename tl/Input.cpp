#include <Windows.h>
#include "Input.h"

bool tl::input::getKey(const int& key) {
	return (GetAsyncKeyState(key) != 0);
}
