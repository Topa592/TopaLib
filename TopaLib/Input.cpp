#include "Input.h"

#include <Windows.h>

bool Input::getKey(const int& key) {
	return (GetAsyncKeyState(key) != 0);
}

bool tl::input::getKey(const int& key) {
	return (GetAsyncKeyState(key) != 0);
}
