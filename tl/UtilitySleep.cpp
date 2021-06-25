#include "Utility.h"
#include <chrono>
#include <thread>

class tl::utility::ConsistantSleep::Impl {
public:
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point sleepExtra;
	std::chrono::duration<double> sleepedExtra = std::chrono::milliseconds(0);
	std::chrono::duration<double> toSleep = std::chrono::milliseconds(0);
};

tl::utility::ConsistantSleep::ConsistantSleep() : impl(new Impl) {}

tl::utility::ConsistantSleep::~ConsistantSleep() {}

void tl::utility::ConsistantSleep::Start() {
	impl->t1 = std::chrono::high_resolution_clock::now();
}

void tl::utility::ConsistantSleep::End(int msTotal) {
	using namespace std;
	impl->sleepExtra = chrono::high_resolution_clock::now();
	auto sleepTime = chrono::milliseconds(msTotal);
	auto timebetweenStartAndEnd = chrono::duration_cast<chrono::duration<double>>
		(chrono::high_resolution_clock::now() - impl->t1);

	impl->toSleep = sleepTime - impl->sleepedExtra - timebetweenStartAndEnd;
	this_thread::sleep_for(impl->toSleep);

	if (impl->toSleep.count() <= 0) impl->toSleep = chrono::milliseconds(0);

	impl->sleepedExtra = chrono::duration_cast<chrono::duration<double>>
		(chrono::high_resolution_clock::now() - impl->sleepExtra) - impl->toSleep;
}

class tl::utility::Timer::Impl {
public:
	std::chrono::high_resolution_clock::time_point resetTime;
};

tl::utility::Timer::Timer() : impl(new Impl) {
	reset();
}

tl::utility::Timer::~Timer() {}

bool tl::utility::Timer::ifTimeReset(int ms) {
	if (ifTime(ms)) {
		reset();
		return true;
	}
	return false;
}

bool tl::utility::Timer::ifTime(int ms) {
	auto t1 = std::chrono::high_resolution_clock::now();
	auto total = (t1 - impl->resetTime);
	return (ms <= (total.count() / 1000000));
}

void tl::utility::Timer::reset() {
	impl->resetTime = std::chrono::high_resolution_clock::now();
}
