/*****************************************************************//**
 * \file   ThreadBase.cpp
 * \brief  A simple encapsulation for 
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include "ThreadBase.hpp"
#include <cassert>

ThreadBase::ThreadBase()
{
	// creat a new Thread , but dont start it yet
	mThreadHdl = CreateThread(
		NULL,               // default security attributes
		100000000,                  // use default stack size  
		ThreadFunc,         // thread function name
		this,               // argument to thread function 
		CREATE_SUSPENDED,   // create suspended
		&mThreadId);        // returns the thread identifier

	assert(mThreadHdl != nullptr);
}

ThreadBase::~ThreadBase()
{
	CloseHandle(mThreadHdl);
}

void ThreadBase::Start() const
{
	ResumeThread(mThreadHdl);
}

void ThreadBase::Stop() const
{
	SuspendThread(mThreadHdl);
}

bool ThreadBase::IsThreadCreated() const
{
	return mThreadHdl != nullptr;
}

HANDLE ThreadBase::GetDuplicateHdl() const
{
	HANDLE hdlDup = nullptr;

	// API Call
	BOOL res = DuplicateHandle(
		GetCurrentProcess(), // source process handle
		mThreadHdl,         // handle to duplicate
		GetCurrentProcess(), // target process handle
		&hdlDup,            // pointer to receive the duplicate handle
		0,                  // desired access (0 means same access)
		FALSE,              // handle is not inheritable
		DUPLICATE_SAME_ACCESS); // options

	assert(res != false); // check if duplication succeeded


	return hdlDup;
}

HANDLE ThreadBase::GetThreadHdl() const
{
	return mThreadHdl;
}

unsigned long WINAPI ThreadBase::ThreadFunc(void* param)
{
	assert(param != nullptr);

	ThreadBase* pObj = static_cast<ThreadBase*>(param);

	pObj->Run();

	// if you are on this position, the thread is going to terminate
	//delete pObj;

	return 0;
}
