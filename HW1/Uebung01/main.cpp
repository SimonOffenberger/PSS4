/*****************************************************************//**
 * \file   main.cpp
 * \brief  
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
#include <windows.h>

using namespace std;

void Print_Fib(size_t n,size_t fib) {
	std::cout.flush();
	std::cout << "WorkerThread " << std::this_thread::get_id() << ": Result of fib("<< n << ") = " << fib << std::endl;
	std::cout.flush();
}

size_t fib(size_t n) {

	if (n <= 1) return n;

	return fib(n - 1) + fib(n - 2);
}

void calculate_fib_sequence(size_t max_n) {
	for(size_t i = 0; i <= max_n; ++i) {
		Print_Fib(i, fib(i));
		Sleep(0);
	}
}

int main(void){
	const size_t num_of_processors = std::thread::hardware_concurrency();
	const size_t max_fib_n = 50;
	const size_t min_threads = 4;
	const size_t num_of_threads = num_of_processors < min_threads ? min_threads : num_of_processors; // Fallback to 4 threads on older systems

	vector<thread> worker_threads;

	worker_threads.reserve(num_of_threads);

	cout << "Detected " << num_of_processors << " logical processors." << endl;

	for(size_t i = 0; i < num_of_processors; ++i) {
		std::thread worker_thread(calculate_fib_sequence, max_fib_n);
		cout.flush();
		cout << "WorkerThread " << worker_thread.get_id() << " created successfully" << endl;
		cout.flush();
		// move WorkerThread into the vector to keep track of it
		worker_threads.emplace_back(move(worker_thread));
	}

	// wait for all the threads to finish their work
	for_each(worker_threads.begin(), worker_threads.end(), [](thread& t) {
		t.join();
	});
}
