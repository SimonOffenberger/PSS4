// This programm starts a new process, eg. msPaint
#include<iostream>
#include<Windows.h> // to access Win32/64 API
#include"Hlp.h"


//using namespace std;

int main() {

	std::cout << "Create a new process" << std::endl;

	// parameters for creating a new process

	STARTUPINFO si; // specifies how the main window should appear [in]
	PROCESS_INFORMATION pi; // filled by CreateProcess with information about 
							// the newly created process and its primary thread [out]
	
	memset(&si, 0, sizeof(si)); // set all parameters of si (struct) to zero
	// memset sets every byte to the specific value -> not the specific datatypes!!!

	si.cb = sizeof(si); // set the size of the startupinfo (byte count)

	memset(&pi, 0, sizeof(pi));


	// start the new process
	if (!CreateProcess(
		0,		    // no module name, use command line
		(LPSTR) "mspaint",  // command line
		0,		    // no process security attribute
		0,		    // no thread security attribute
		false,      // no inheritance
		0,		    // no creation flags
		0,			// use parent's environment block
		0,			// use parent's starting directory
		&si,		// pointer to the startupinfo struct
		&pi			// pointer to the process_information struct
	)) {
		std::cerr << "CreateProcess failed. Error: "<< Hlp::ErrMsg(GetLastError()) << std::endl;
		return -1;
	}

	// process id of the generated child process (stored in process_information)
	std::cout << "CreateProcess returend, PID: " << pi.dwProcessId << std::endl;

	Sleep(5000); // wait for 5 sec...

	if (!TerminateProcess(pi.hProcess, 0)) std::cerr << "Error: "<< Hlp::ErrMsg(GetLastError()) << std::endl;



	// wait until the new process terminates
	WaitForSingleObject(pi.hProcess, INFINITE); // API call

	// cleanup -> Detach from the parent process
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	// Handle: Eindeutige Adresse (void*) auf eine Resource des Systems

	return 0;
}