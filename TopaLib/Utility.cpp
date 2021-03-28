#include "Utility.h"
#include <Windows.h>
#include <chrono>
#include <thread>

struct tl::utility::dataTypes::DataConstSleep {
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point sleepExtra;
	std::chrono::duration<double> sleepedExtra = std::chrono::milliseconds(0);
	std::chrono::duration<double> toSleep = std::chrono::milliseconds(0);
};

void tl::utility::ConstSleep::start() {
	using namespace std::chrono;
	data->t1 = high_resolution_clock::now();
}

void tl::utility::ConstSleep::end() {
	using namespace std::chrono;
	using namespace std;
	data->sleepExtra = high_resolution_clock::now();
	data->toSleep = milliseconds(ms) - data->sleepedExtra - duration_cast<duration<double>>(high_resolution_clock::now() - data->t1);
	this_thread::sleep_for(data->toSleep);
	if (data->toSleep.count() <= 0) data->toSleep = milliseconds(0);
	data->sleepedExtra = duration_cast<duration<double>>(high_resolution_clock::now() - data->sleepExtra) - data->toSleep;
}

tl::utility::ConstSleep::ConstSleep(int ms) : data(new dataTypes::DataConstSleep()), ms(ms) {}