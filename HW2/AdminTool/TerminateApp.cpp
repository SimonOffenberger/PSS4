#include "TerminateApp.hpp"

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
	return "Terminate Application : " + mApp;
}
