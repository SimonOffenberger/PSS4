/*****************************************************************//**
 * \file   main.cpp
 * \brief  
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include "ThreadImpl.hpp"
#include <iostream>

int main(void) {

	ThreadImpl *  pthread1 = new ThreadImpl;
	ThreadImpl *  pthread2 = new ThreadImpl;
	ThreadImpl *  pthread3 = new ThreadImpl;

	pthread1->Init(1, THREAD_PRIORITY_HIGHEST);
	pthread2->Init(2, THREAD_PRIORITY_HIGHEST);
	pthread3->Init(3, THREAD_PRIORITY_HIGHEST);

	// fetch thread handles for sync
	int const n = 3;
	HANDLE HDL[n];

	HDL[0] = pthread1->GetDuplicateHdl();
	HDL[1] = pthread2->GetDuplicateHdl();
	HDL[2] = pthread3->GetDuplicateHdl();

	pthread1->Start();
	pthread2->Start();
	pthread3->Start();

	// syn main thread to terminate worker
	Sleep(2000);

	WaitForMultipleObjects(n, HDL, TRUE, INFINITE);

	// cleanup
	CloseHandle(HDL[0]);
	CloseHandle(HDL[1]);
	CloseHandle(HDL[2]);

	std::cout << "All done." << std::endl;

	// note: there is no memory leak as the threads remove thermself;

	return 0;
}
