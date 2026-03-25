#include "TerminateApp.hpp"
#include <sstream>

TerminateApp::TerminateApp(const DWORD app)
{
	mApp = app;
}

void TerminateApp::Execute()
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, mApp);

	TerminateProcess(hProcess, 0);
}

std::string TerminateApp::GetCmdName() const
{

	std::stringstream converter;

	converter << TerminateApp::CMD_IDENTIFIER;
	converter << " -> Terminate Application PID: ";
	converter << mApp;

	return converter.str();
}

std::string TerminateApp::GetCmdIdentifier() const
{
	return TerminateApp::CMD_IDENTIFIER;
}

