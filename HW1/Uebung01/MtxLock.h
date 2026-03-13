#ifndef MTXLOCK_INCLUDED
#define MTXLOCK_INCLUDED

#include <windows.h>
#include <cassert>


// -----------------------------------------------------------
// mutual exclusion for synchronization with mutex sync-object
// mb / SEN4 / HSD / Hagenberg
//

/* usage:
   ------
 Mutex MtxAccess;                   // create Mutex Scoped Locking Object, or
 Mutex MtxAccess("MyMutex");        // create Mutex Scoped Locking Object with name

 {
    MtxLock Lock(MtxAccess);        // engage Lock
    ...
 }                                  // <-- automatic release

*/


// do the setup of the mutex object
// --------------------------------
class Mutex
{
    friend class MtxLock;

public:
    // CTor
    Mutex()
    {
        mMtx = CreateMutex(0, false, 0);
    }
    // Overridden CTor takes a Mutex name
    // Set the flag 'OpenMutex' to true, if you want to open an already existing Mutex and you are *sure*, it exists.
    // Leave the flag 'OpenMutex' on false, if you are uncertain, if it has already been created (due to a race condition).
    // If you are in doubt (and to be safe), just call:  Mutex mtx("MyMutexName");
    Mutex(std::string const & MtxName, bool OpenMtx = false)
    {
        if (!OpenMtx)
        {
            mMtx = CreateMutex(0, false, MtxName.c_str());
        }
        else
        {
            mMtx = OpenMutex(MUTEX_ALL_ACCESS, false, MtxName.c_str());
        }
    }

    // returns true, if the Mutex has been created or opened successfully
    //         false, otherwise (use GetLastError() to get further information)
    // use this in an assertions after object creation: assert(mtx.IsValid());
    bool IsValid()
    {
        return mMtx != 0;
    }


    // DTor
    ~Mutex()
    {
        CloseHandle(mMtx);
    }


private:
    void Acquire()
    {
        DWORD res = WaitForSingleObject(mMtx, INFINITE);
        assert(res == WAIT_OBJECT_0);
    }

    void Release()
    {
        BOOL res = ReleaseMutex(mMtx);
        assert(res != 0);
    }

    // tries to get the mutex, but does NOT block at all:
    // returns true, if the mutex has been got
    //         false, otherwise
    // note: function unused so far
    bool TryToAcquire() {
        return WaitForSingleObject(mMtx, 0) == WAIT_OBJECT_0;
    }


    Mutex(Mutex const &);				// do not allow copying
    Mutex & operator = (Mutex const &); // do not allow assignment

    HANDLE mMtx;			            // the mutex handle
};


// apply and release the MtxLock
// -----------------------------
class MtxLock
{
public:

    // Lock for exclusive access
    MtxLock(Mutex & MtxObj)
        :mMtxAccess(MtxObj)
    {
        mMtxAccess.Acquire();
    }

    // release Lock
    ~MtxLock()
    {
        mMtxAccess.Release();
    }

private:
    MtxLock();								  // do not allow default CTor
    MtxLock(MtxLock const &);			      // do not allow copying
    MtxLock & operator = (MtxLock const &);	  // do not allow assignment

    Mutex &mMtxAccess;
};

#endif
