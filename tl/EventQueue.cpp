#include "EventQueue.h"
#include <vector>
#include <queue>

namespace {
	std::vector<void(*)(tl::datatypes::Point point)> Functions;
	
}

void tl::eventQue::mouse::addFuncOnLButtonDown(void(*func)(tl::datatypes::Point point)) {
	
}

void tl::eventQue::run() {

}

void tl::eventQue::clear() {

}

void tl::eventQue::deleteFunctions() {

}
