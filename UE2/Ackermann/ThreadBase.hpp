#ifndef ThreadBase_HPP
#define ThreadBase_HPP
/*****************************************************************//**
 * \file   ThreadBase.hpp
 * \brief  A simple encapsulation for thread
 * \brief  use thes as a base class.
 * \brief  Derived Classes should provide an Init() Methode
 * \brief and must override the pure virtual Run() Methode.
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include <Windows.h>


class ThreadBase
{
public:
	// Ctor and Dtor
	ThreadBase();
	virtual ~ThreadBase();

	// The thread function
	virtual int Run() = 0;

	// control thread behavior
	virtual void Start() const;
	virtual void Stop() const;

	/**
	 * \brief State Check.
	 * 
	 * \return true -> thread has been created
	 * \return false -> thread has not been created
	 */
	virtual bool IsThreadCreated() const;

	/**
	 * \brief Handle ist eindeutige ressource auf den Thread.
	 * \brief This returns a duplicate handle to solve lifetime issues.
	 * \brief when the original handle is closed, the duplicate handle is still valid.
	 * \brief be use on wait functions
	 * 
	 * \return Duplicate handle to the thread, caller is responsible for closing it.
	 */
	virtual HANDLE GetDuplicateHdl() const;

protected:
	/**
	 * \brief returns the interal thread handle for derived classes only.
	 * 
	 * \return 
	 */
	virtual HANDLE GetThreadHdl() const;

	// dont allow copying and assignment
	ThreadBase(ThreadBase const&) = delete;
	ThreadBase & operator = (ThreadBase const&) = delete;
private:

	// the thread function
	static unsigned long WINAPI ThreadFunc(void* param);

	HANDLE mThreadHdl;
	unsigned long mThreadId;
};

#endif // !ThreadBase
