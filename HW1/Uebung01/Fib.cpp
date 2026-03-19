/*****************************************************************//**
 * @file Fib.cpp
 * @brief Implementation of simple Fibonacci helpers and multi-threaded demos.
 *
 * Contains recursive fibonacci implementation and
 * benchmark/printing helpers that spawn Windows threads.
 *********************************************************************/
#include "Fib.hpp"
#include <thread>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <winerror.h>
#include <string>
#include "StopWatch.h"
#include "Hlp.h"


using namespace std;

const string ERROR_CREATING_THREAD = "Failed to create thread: ";

/**
 * @brief Print the computed Fibonacci value from a worker thread.
 *
 * Prints a single line identifying the worker thread and the computed
 * Fibonacci value for the given input.
 *
 * @param n Input index to fib().
 * @param fib Result of fib(n).
 */
void Print_Fib(const size_t n,const size_t fib) {
	std::cout.flush();
	std::cout << "WorkerThread " << std::this_thread::get_id();
	std::cout << ": Result of fib(" << n << ") = " << fib << std::endl;
	std::cout.flush();
}

/**
 * @brief Recursive Fibonacci implementation.
 *
 * Computes the nth Fibonacci number using a recursive algorithm.
 *
 * @param n Fibonacci index.
 * @return fib(n).
 */
size_t fib(const size_t n) {

	if (n <= 1) return n;

	return fib(n - 1) + fib(n - 2);
}

/**
 * @brief Thread procedure to calculate a single fib(n) and print the result.
 *
 * This function is intended to be used as a Windows thread entry point.
 * It expects a pointer to a `size_t` containing the input `n`. The thread
 * computes `fib(n)` and prints the result via `Print_Fib`.
 *
 * @param n Pointer to `size_t` containing the input n (passed as LPVOID).
 * @return DWORD Thread exit code (0 on success).
 */
DWORD WINAPI calculate_fib(LPVOID n) {

	const size_t num = *(static_cast<size_t*>(n));

	Print_Fib(num, fib(num));

	return NO_ERROR;
}

/**
 * @brief Thread procedure to print the full Fibonacci sequence 0..max_n.
 *
 * This function is intended to be used as a Windows thread entry point.
 * It expects a pointer to a `size_t` containing the maximum `n`. The thread
 * iterates from 0..max_n computing and printing each Fibonacci value.
 *
 * @param max_n Pointer to `size_t` containing the maximum n (passed as LPVOID).
 * @return DWORD Thread exit code (0 on success).
 */
DWORD WINAPI calculate_fib_sequence(LPVOID max_n) {

	const size_t max_num = *(static_cast<size_t*>(max_n));

	for (size_t i = 0; i <= max_num; ++i) {
		Print_Fib(i, fib(i));
	}

	return NO_ERROR;
}


/**
 * @brief Spawn multiple threads that print the Fibonacci sequence up to `max_fib_n`.
 *
 * Determines the number of logical processors and spawns one worker thread per
 * logical processor (with a minimum fallback of 4 threads). Each worker thread
 * executes `calculate_fib_sequence` with a pointer to `max_fib_n`.
 *
 * Note: This function throws `std::runtime_error` if a thread cannot be created.
 *
 * @param max_fib_n Maximum Fibonacci index to print (each thread prints 0..max_fib_n).
 */
void PrintFibSequenceMultiThreaded(const size_t max_fib_n) {

	// get the number of logical processors available on the system
	// if the number of logical processors is less than 4, use 4 threads as a fallback (for older systems)
	const size_t num_of_processors = std::thread::hardware_concurrency();
	const size_t min_threads = 4;
	const size_t num_of_threads = num_of_processors < min_threads ? min_threads : num_of_processors;
	size_t fib_n = max_fib_n;

	// vectors to store the handles and thread IDs of the worker threads
	vector<HANDLE> worker_threads;
	vector<DWORD> thread_ids(num_of_threads, 0);

	// reserve space in the vectors to avoid reallocations
	worker_threads.reserve(num_of_threads);

	cout << "Detected " << num_of_processors << " logical processors." << endl;

	for (size_t i = 0; i < num_of_processors; ++i) {

		// create a new worker thread and call the calculate_fib_sequence function
		// handle -> void* address of the thread
		HANDLE Worker = CreateThread(
			0,
			0, // default stack size (1MB), value determines the number of bytes
			calculate_fib_sequence,
			&fib_n,
			0,
			&thread_ids.at(i)
		);

		if (Worker == nullptr) {
			throw runtime_error(ERROR_CREATING_THREAD + Hlp::ErrMsg(GetLastError()));
		}

		worker_threads.emplace_back(move(Worker));

		cout << "Created thread with ID: " << thread_ids.back() << endl;
	}


	// Wait for all worker threads to finish and close their handles
	for_each(worker_threads.cbegin(), worker_threads.cend(), [](const HANDLE& hThread) {
		// wait for the thread to finish
		WaitForSingleObject(hThread, INFINITE);

		// Return Value of the thread
		DWORD exitCode = 0;
		GetExitCodeThread(hThread, &exitCode);
		if (exitCode != NO_ERROR) {
			throw runtime_error("Thread Exited with error: " + exitCode + Hlp::ErrMsg(exitCode));
		}

		CloseHandle(hThread);
	});
}



/**
 * @brief Benchmark single-threaded vs multi-threaded Fibonacci computation.
 *
 * Measures the time to compute `fib(max_fib_n)` `k` times in both single-threaded
 * and multi-threaded modes, where `k` equals the number of logical processors
 * (with a minimum fallback of 4). The multi-threaded version spawns one thread
 * per processor that executes `calculate_fib`.
 *
 * Note: This function throws `std::runtime_error` if a thread cannot be created.
 *
 * @param max_fib_n Fibonacci index to compute in benchmarks.
 */
void BenchmarkFib(const size_t max_fib_n) {

	const size_t num_of_processors = std::thread::hardware_concurrency();
	const size_t min_threads = 4;
	const size_t num_of_threads = num_of_processors < min_threads ? min_threads : num_of_processors; // Fallback to 4 threads on older systems
	size_t fib_n = max_fib_n;

	// vectors to store the handles and thread IDs of the worker threads
	vector<HANDLE> worker_threads;
	vector<DWORD> thread_ids(num_of_threads, 0);
	// reserve space in the vectors to avoid reallocations
	worker_threads.reserve(num_of_threads);


	// c)
	// Calculation of the speedup of the parallelized version compared to a single-threaded version
	// first calculate k-Times the fib of (n) in a single-threaded version and measure the time
	// then calculate k-Times the fib of (n) in a multi-threaded version and measure the time

	// Single Threaded Version k-Times fib(n)
	cout << "Calculating fib(" << max_fib_n << ") in a single-threaded version..." << endl;

	// start the stopwatch to measure the time taken for the single-threaded version
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

		// create a new worker thread and call the calculate_fib function
		// handle -> void* address of the thread
		HANDLE Worker = CreateThread(
			0,
			0, // default stack size (1MB), value determines the number of bytes
			calculate_fib,
			&fib_n,
			0,
			&thread_ids.at(i)
		);

		if(Worker == nullptr) {
			throw runtime_error(ERROR_CREATING_THREAD + Hlp::ErrMsg(GetLastError()));
		}

		worker_threads.emplace_back(move(Worker));
	}

	// Wait for all worker threads to finish and close their handles
	for_each(worker_threads.cbegin(), worker_threads.cend(), [](const HANDLE& hThread) {
		WaitForSingleObject(hThread, INFINITE);

		// Return Value of the thread
		DWORD exitCode = 0;
		GetExitCodeThread(hThread, &exitCode);
		if (exitCode != NO_ERROR) {
			throw runtime_error("Thread Exited with error: " + exitCode + Hlp::ErrMsg(exitCode));
		}

		CloseHandle(hThread);
	});

	multi_threaded_time = stw::Stop_ms();

	cout << endl << "Time taken for multi-threaded version: " << multi_threaded_time << " ms" << endl;

	if (multi_threaded_time > 0) {
		cout << endl << "Speedup: " << single_threaded_time / multi_threaded_time << "x" << endl << endl;
	}
	else {
		cerr << "Multi-threaded time is zero, cannot calculate speedup." << endl;
	}
}

