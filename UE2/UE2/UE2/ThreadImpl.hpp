/*****************************************************************//**
 * \file   ThreadImpl.hpp
 * \brief  Implementation of the ThreadBase class, this is where the thread function is defined.
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/
#ifndef THREAD_IMPL_HPP
#define THREAD_IMPL_HPP

#include "ThreadBase.hpp"

class ThreadImpl : public ThreadBase
{
public:
	ThreadImpl();

	virtual ~ThreadImpl();

	/**
	 * \brief Initializing Methode.
	 * 
	 * \param number
	 * \param threadPrio
	 */
	virtual void Init(const int number,const int threadPrio = THREAD_PRIORITY_NORMAL);

	virtual int Run() override;

private:
	int mThreadPriority; // Prioirty of the thread, default is THREAD_PRIORITY_NORMAL
	bool mIsInitialized;	 // Flag to check if the thread has been initialized, default is false (0)
	int mThreadNumber;	 // Number to identify the thread, default is 0
	
};

#endif // !THREAD_IMPL_HPP
