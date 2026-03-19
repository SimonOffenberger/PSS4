/*****************************************************************//**
 * \file   main.cpp
 * \brief  
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include "ThreadImpl.hpp"
#include <iostream>
#include <conio.h>

using namespace std;

int main(void) {

	ThreadImpl* pThread1 = new ThreadImpl();
	ThreadImpl* pThread2 = new ThreadImpl();
	ThreadImpl* pThread3 = new ThreadImpl();

	pThread1->Init(1, THREAD_PRIORITY_LOWEST);
	pThread2->Init(2, THREAD_PRIORITY_NORMAL);
	pThread3->Init(3, THREAD_PRIORITY_HIGHEST);

	pThread1->Start();
	pThread2->Start();
	pThread3->Start();

	// do something in the main thread
	Sleep(100);

	cout << "When done, press a key to exit..." << endl;
	_getch(); // poor mans way to sync

	cout << "All Done!" << endl; 

	return 0;
}
