#include <iomanip>
#include "ListApps.hpp"
#include "windows.h"
#include <iostream>


void ListApps::Execute()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 entry;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL,NULL);

	PrintHeader();

	bool retval = Process32First(hProcessSnap,&entry);

	while (retval) {
		PrintProcessInfo(entry);
		retval = Process32Next(hProcessSnap,&entry);
	}

	CloseHandle(hProcessSnap);
}

std::string ListApps::GetCmdName() const
{
	return ListApps::CMD_IDENTIFIER + " -> List Applications";
}

std::string ListApps::GetCmdIdentifier() const
{
	return ListApps::CMD_IDENTIFIER;
}


static const char* PriorityToString(LONG priority)
{
	if (priority <= 4)  return "low";
	if (priority >= 10) return "high";
	return "normal";
}

void ListApps::PrintHeader() const
{
	mOst << std::left
		<< std::setw(cProcessNameWidth) << "Process"
		<< std::setw(cProcessPIDWidth) << "PID"
		<< std::setw(cProcessPrioWidth) << "BasePriority"
		<< std::setw(cProcessCntTHWidth) << "Thread Count"
		<< '\n';

	mOst << std::string(cProcessNameWidth+ cProcessPIDWidth+ cProcessPrioWidth+ cProcessCntTHWidth, '-') << '\n';
}

void ListApps::PrintProcessInfo(const PROCESSENTRY32& entry) const
{
	mOst << std::left
		<< std::setw(cProcessNameWidth) << entry.szExeFile
		<< std::setw(cProcessPIDWidth) << entry.th32ProcessID
		<< std::setw(cProcessPrioWidth) << PriorityToString(entry.pcPriClassBase)
		<< std::setw(cProcessCntTHWidth) << entry.cntThreads
		<< '\n';
}
