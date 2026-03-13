// Create some workerthreads within our process
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include"Hlp.h"


// global variables
size_t const n = 100;

DWORD WINAPI ThreadFunc(LPVOID threadNumber);


int main() {

	std::cout << "Create a thread and execute some code: " << std::endl;

	// data needed for CreateThread-API
	DWORD idThread1 = 0;
	DWORD idThread2 = 0;

	// personal thread number
	size_t myThreadNum1 = 1;
	size_t myThreadNum2 = 2;

	// create a new worker thread and call the ThreadFunc function
	// handle -> void* Adresse vom Thread
	HANDLE hTread1 = CreateThread(
		0,
		0, // default stack size (1MB), value determines the number of bytes
		ThreadFunc,
		&myThreadNum1,
		0,
		&idThread1
	);

	HANDLE hTread2 = CreateThread(
		0,
		0, // default stack size (1MB), value determines the number of bytes
		ThreadFunc,
		&myThreadNum2,
		0,
		&idThread2
	);

	// some work for our mainthread

	for (int i = 0; i < n; i++) {
		DWORD idMainThread = GetCurrentThreadId(); // DWORD = unsigned long -> typedef

		std::cout << "MainThread with ID ";
		std::cout << idMainThread;
		std::cout << ": Loop # ";
		std::cout << i;
		std::cout << std::endl;
	}


	std::cout << "Press a key..." << std::endl;
	
	_getch(); // poor man's sync: prevent main thread from termination

	CloseHandle(hTread1);
	CloseHandle(hTread2);

	// output ist random every time -> do to parallelity of the threads...

	return 0;
}


// this code will be run from the workerthread
DWORD WINAPI ThreadFunc(LPVOID threadNumber) {

	size_t num = *(static_cast<size_t*>(threadNumber)); // specific cpp cast

	for (int i = 0; i < n; i++) {
		DWORD currentThreadId = GetCurrentThreadId();
		std::cout << "WorkerThread";
		std::cout << num;
		std::cout << " with ID " << currentThreadId;
		std::cout << "Loop # ";
		std::cout << i;
		std::cout << std::endl;
	}
	// worker thread closes -> main thread will resume
	return 0;
}
