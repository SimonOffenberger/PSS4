/*****************************************************************//**
 /**
 * \file   OpenApp.cpp
 * \brief  Implementation of the OpenApp command.
 * 
 * \author Simon
 * \date   March 2026
 *********************************************************************/

#include "OpenApp.hpp"
#include "windows.h"
#include "Hlp.h"
#include <iostream>
#include <vector>


void OpenApp::Execute(const std::string& cmdArg)
{
    if (cmdArg.empty())
	{
		throw std::invalid_argument("No application specified.");
	}

	// parameters for creating a new process
	//ost << "Enter the name of the application to open (e.g. mspaint): " << std::endl << ">";
	//std::string app;
	//in >> app;

	STARTUPINFO si; // specifies how the main window should appear [in]
	PROCESS_INFORMATION pi; // filled by CreateProcess with information about 
	// the newly created process and its primary thread [out]

	memset(&si, 0, sizeof(si)); // set all parameters of si (struct) to zero
	// memset sets every byte to the specific value -> not the specific datatypes!!!

	si.cb = sizeof(si); // set the size of the startupinfo (byte count)

	memset(&pi, 0, sizeof(pi));

	// CreateProcess may modify the command line buffer; provide a writable copy.
	std::vector<char> cmdLine(cmdArg.begin(), cmdArg.end());
	cmdLine.push_back('\0');

	// start the new process
	if (!CreateProcess(
		0,		    // no module name, use command line
     cmdLine.data(),  // command line
		0,		    // no process security attribute
		0,		    // no thread security attribute
		false,      // no inheritance
		0,		    // no creation flags
		0,			// use parent's environment block
		0,			// use parent's starting directory
		&si,		// pointer to the startupinfo struct
		&pi			// pointer to the process_information struct
	)) {
		throw std::runtime_error(ERROR_CREATE_PROCESS_FAILED + Hlp::ErrMsg(GetLastError()));
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

std::string OpenApp::GetCmdName() const
{
	return std::string(OpenApp::CMD_IDENTIFIER) + " -> Open Application (Usage: exec <app_name>)";
}

std::string OpenApp::GetCmdIdentifier() const
{
	return OpenApp::CMD_IDENTIFIER;
}

