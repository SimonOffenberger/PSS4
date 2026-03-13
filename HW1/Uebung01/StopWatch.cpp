#include <chrono>
#include "StopWatch.h"

auto start = std::chrono::time_point<std::chrono::system_clock> ();

void stw::Start() {
	start = std::chrono::system_clock::now();
}

double stw::Stop() {
	std::chrono::nanoseconds duration = std::chrono::system_clock::now() - start;
	return duration.count() / 1e9;  // seconds
}

double stw::Stop_ms() {
	std::chrono::nanoseconds duration = std::chrono::system_clock::now() - start;
	return duration.count() / 1e6;  // milliseconds
}


