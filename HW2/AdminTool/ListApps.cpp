#include <iomanip>
/**
 * @file ListApps.cpp
 * @brief Implementation of the ListApps command.
 */

#include "ListApps.hpp"
#include "windows.h"
#include <iostream>


void ListApps::Execute(const std::string& cmdArg)
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 entry;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL,NULL);

	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		throw  std::invalid_argument( ERROR_SNAPSHOT_FAILED + GetLastError());
	}

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
	return std::string(ListApps::CMD_IDENTIFIER) + " -> List Applications (Usage: lsa)";
}

std::string ListApps::GetCmdIdentifier() const
{
	return ListApps::CMD_IDENTIFIER;
}


static const char* PriorityToString(const LONG priority)
{
	if (priority <= ListApps::cLowPrioThreshold)  return "low";
	if (priority >= ListApps::cHighPrioThreshold) return "high";
	return "normal";
}

void ListApps::PrintHeader() const
{
	if (mOst.bad()) {
		throw std::runtime_error(ERROR_BAD_OSTREAM);
	}

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
	if (mOst.bad()) {
		throw std::runtime_error(ERROR_BAD_OSTREAM);
	}

	mOst << std::left
		<< std::setw(cProcessNameWidth) << entry.szExeFile
		<< std::setw(cProcessPIDWidth) << entry.th32ProcessID
		<< std::setw(cProcessPrioWidth) << PriorityToString(entry.pcPriClassBase)
		<< std::setw(cProcessCntTHWidth) << entry.cntThreads
		<< '\n';
}
