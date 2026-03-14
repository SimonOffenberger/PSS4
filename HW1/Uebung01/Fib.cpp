/*****************************************************************//**
 * \file   Fib.cpp
 * \brief  
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include "Fib.hpp"
#include <thread>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "StopWatch.h"
#include "Hlp.h"

using namespace std;

DWORD WINAPI calculate_fib_sequence(LPVOID max_n);

void Print_Fib(size_t n, size_t fib) {
	std::cout.flush();
	std::cout << "WorkerThread " << std::this_thread::get_id();
	Sleep(0);
	std::cout << ": Result of fib(" << n << ") = " << fib << std::endl;
	std::cout.flush();
}

size_t fib(size_t n) {

	if (n <= 1) return n;

	return fib(n - 1) + fib(n - 2);
}

DWORD WINAPI calculate_fib(LPVOID n) {

	const size_t num = *(static_cast<size_t*>(n));

	Print_Fib(num, fib(num));

	return 0;
}


DWORD WINAPI calculate_fib_sequence(LPVOID max_n) {

	const size_t max_num = *(static_cast<size_t*>(max_n));

	for (size_t i = 0; i <= max_num; ++i) {
		Print_Fib(i, fib(i));
		Sleep(0);
	}

	return 0;
}



void PrintFibSequenceMultiThreaded(size_t max_fib_n) {

	const size_t num_of_processors = std::thread::hardware_concurrency();
	const size_t min_threads = 4;
	const size_t num_of_threads = num_of_processors < min_threads ? min_threads : num_of_processors; // Fallback to 4 threads on older systems

	vector<HANDLE> worker_threads;
	vector<DWORD> thread_ids(num_of_threads, 0);

	worker_threads.reserve(num_of_threads);

	cout << "Detected " << num_of_processors << " logical processors." << endl;

	for (size_t i = 0; i < num_of_processors; ++i) {

		// create a new worker thread and call the calculate_fib_sequence function
		// handle -> void* Adresse vom Thread
		worker_threads.emplace_back(CreateThread(
			0,
			0, // default stack size (1MB), value determines the number of bytes
			calculate_fib_sequence,
			&max_fib_n,
			0,
			&thread_ids.at(i)
		));

		cout << "Created thread with ID: " << thread_ids.back() << endl;
	}

	WaitForMultipleObjects(static_cast<DWORD>(worker_threads.size()), worker_threads.data(), TRUE, INFINITE);

	for_each(worker_threads.cbegin(), worker_threads.cend(), [](const HANDLE& hThread) {
		CloseHandle(hThread);
	});
}



void BenchmarkFib(size_t max_fib_n) {

	const size_t num_of_processors = std::thread::hardware_concurrency();
	const size_t min_threads = 4;
	const size_t num_of_threads = num_of_processors < min_threads ? min_threads : num_of_processors; // Fallback to 4 threads on older systems

	vector<HANDLE> worker_threads;
	vector<DWORD> thread_ids(num_of_threads, 0);

	worker_threads.reserve(num_of_threads);


	// c)
	// Calculation of the speedup of the parallelized version compared to a single-threaded version
	// first calculate k-Times the fib of (n) in a single-threaded version and measure the time
	// then calculate k-Times the fib of (n) in a multi-threaded version and measure the time

	// Single Threaded Version k-Times fib(n)



	cout << "Calculating fib(" << max_fib_n << ") in a single-threaded version..." << endl;

	double single_threaded_time = 0.0;
	double multi_threaded_time = 0.0;

	stw::Start();

	for (size_t i = 0; i < num_of_processors; ++i) {
		cout << "Single Threaded: Iteration " << i << " of " << num_of_processors << " fib(" << max_fib_n << ") = " << fib(max_fib_n) << endl;
	}
	single_threaded_time = stw::Stop_ms();

	cout << endl << "Time taken for single-threaded version: " << single_threaded_time << " ms" << endl;



	// Multi Threaded Version k-Times fib(n)

	cout << "Calculating fib(" << max_fib_n << ") in a multi-threaded version..." << endl;

	stw::Start();

	for (size_t i = 0; i < num_of_processors; ++i) {

		// create a new worker thread and call the calculate_fib_sequence function
		// handle -> void* Adresse vom Thread
		worker_threads.emplace_back(CreateThread(
			0,
			0, // default stack size (1MB), value determines the number of bytes
			calculate_fib,
			&max_fib_n,
			0,
			&thread_ids.at(i)
		));

	}

	WaitForMultipleObjects(static_cast<DWORD>(worker_threads.size()), worker_threads.data(), TRUE, INFINITE);

	for_each(worker_threads.cbegin(), worker_threads.cend(), [](const HANDLE& hThread) {
		CloseHandle(hThread);
		});

	multi_threaded_time = stw::Stop_ms();

	cout << endl << "Time taken for multi-threaded version: " << multi_threaded_time << " ms" << endl;

	cout << endl << "Speedup: " << single_threaded_time / multi_threaded_time << "x" << endl;
}

