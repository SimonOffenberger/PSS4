/*****************************************************************//**
 * \file   ThreadImpl.cpp
 * \brief
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include "ThreadImpl.hpp"
#include <cassert>
#include <iostream>
#include <vld.h>

ThreadImpl::ThreadImpl()
{
	// sanity check for the base class constructor
	assert(ThreadBase::IsThreadCreated() == true);

	// Init() not called so far
	mIsInitialized = false;
	mThreadNumber = 0;

	// fetch the initial thread priority
	mThreadPriority = GetThreadPriority(GetThreadHdl());

	std::cout << "Initial Thread Priority: " << mThreadPriority << std::endl;
}

ThreadImpl::~ThreadImpl()
{
}

void ThreadImpl::Init(const int number,const int threadPrio)
{
	mThreadNumber = number;
	mThreadPriority = threadPrio;

	SetThreadPriority(GetThreadHdl(), mThreadPriority);

	mIsInitialized = true;
}

int ThreadImpl::Run()
{
	// take care of the thread has been initialized before running the thread function
	assert(mIsInitialized == true); // check if the thread has been initialized

	if(!mIsInitialized)
	{
		return 0;
	}

	// ---- enter your personal code right here ----

	DWORD threadId = GetCurrentThreadId();
	mThreadPriority = GetThreadPriority(GetThreadHdl());

	std::cout << "[TID: " << threadId << "] Thread Number: " << mThreadNumber << ", Thread Priority: " << mThreadPriority << std::endl;
	

	// --- end of personal code section

	// remove yourself 
	delete this;

	return 0;
}
