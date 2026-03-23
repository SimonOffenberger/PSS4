/*****************************************************************//**
 * \file   OpenApp.cpp
 * \brief  
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include "OpenApp.hpp"
#include "windows.h"
#include "Hlp.h"
#include <iostream>

OpenApp::OpenApp(const std::string& app)
{
	mApp = app;
}

void OpenApp::Execute()
{
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
		(LPSTR)mApp.c_str(),  // command line
		0,		    // no process security attribute
		0,		    // no thread security attribute
		false,      // no inheritance
		0,		    // no creation flags
		0,			// use parent's environment block
		0,			// use parent's starting directory
		&si,		// pointer to the startupinfo struct
		&pi			// pointer to the process_information struct
	)) {
		std::cerr << "CreateProcess failed. Error: " << Hlp::ErrMsg(GetLastError()) << std::endl;
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

}

std::string OpenApp::GetCmdName() const
{
	return "Open Application : " + mApp;
}
