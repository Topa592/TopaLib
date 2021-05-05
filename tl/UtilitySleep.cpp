#include "Utility.h"
#include <chrono>
#include <thread>

std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point sleepExtra;
std::chrono::duration<double> sleepedExtra = std::chrono::milliseconds(0);
std::chrono::duration<double> toSleep = std::chrono::milliseconds(0);

void tl::utility::sleep::Start() {
	t1 = std::chrono::high_resolution_clock::now();
}

void tl::utility::sleep::End(int msTotal) {
	using namespace std;
	sleepExtra = chrono::high_resolution_clock::now();
	toSleep = chrono::milliseconds(msTotal) - sleepedExtra
		- chrono::duration_cast<chrono::duration<double>>
		(chrono::high_resolution_clock::now() - t1);
	this_thread::sleep_for(toSleep);
	if (toSleep.count() <= 0) toSleep = chrono::milliseconds(0);

	sleepedExtra = chrono::duration_cast<chrono::duration<double>>
		(chrono::high_resolution_clock::now() - sleepExtra) - toSleep;
}
