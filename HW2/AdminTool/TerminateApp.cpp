/**
 * @file TerminateApp.cpp
 * @brief Implementation of the TerminateApp command.
 */
#include "TerminateApp.hpp"
#include <sstream>
#include <string>
#include "Hlp.h"



void TerminateApp::Execute(const std::string & cmdArg)
{

	DWORD mApp = 0;

	std::stringstream converter;
	converter << cmdArg;
	converter >> mApp;

	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, mApp);

	if(hProcess == NULL)
	{
		throw std::runtime_error(ERROR_TERMINATE_PROCESS_FAILED + std::to_string(mApp) + ". Error: " + Hlp::ErrMsg(GetLastError()));
	}

	TerminateProcess(hProcess, 0);
   CloseHandle(hProcess);
}

std::string TerminateApp::GetCmdName() const
{

	std::stringstream converter;

	converter << TerminateApp::CMD_IDENTIFIER;
	converter << " -> Terminate Application (Usage: term <PID>)";

	return converter.str();
}

std::string TerminateApp::GetCmdIdentifier() const
{
	return TerminateApp::CMD_IDENTIFIER;
}

