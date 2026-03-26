
/**
 * @file ListSystemInfo.cpp
 * @brief Implementation of the ListSystemInfo command.
 */
#include "ListSystemInfo.hpp"
#include <windows.h>
#include <VersionHelpers.h>
#include <iostream>
#include <iomanip>
#include <string>

static const char* GetArchitectureString(WORD arch)
{
    switch (arch)
    {
    case PROCESSOR_ARCHITECTURE_INTEL:
        return "Intel CPU or compatibles";
    case PROCESSOR_ARCHITECTURE_AMD64:
        return "x64 (AMD or Intel)";
    case PROCESSOR_ARCHITECTURE_ARM:
        return "ARM";
    case PROCESSOR_ARCHITECTURE_ARM64:
        return "ARM64";
    default:
        return "unknown";
    }
}

static std::string GetOSVersionString()
{
    if (IsWindows10OrGreater())
        return "Windows 10 or greater";
    if (IsWindows8Point1OrGreater())
        return "Windows 8.1 or greater";
    if (IsWindows8OrGreater())
        return "Windows 8 or greater";
    if (IsWindows7OrGreater())
        return "Windows 7 or greater";

    return "Older than Windows 7";
}


void ListSystemInfo::Execute(const std::string& cmdArg)
{
	PrintHardwareInfo();
	PrintSoftwareInfo();
}

void ListSystemInfo::PrintHardwareInfo()
{
    if(mOst.bad())
    {
        throw std::runtime_error(ERROR_BAD_OSTREAM);
	}

    SYSTEM_INFO si{};
    GetSystemInfo(&si);

    mOst << "System Information <HARDWARE>:\n";
    mOst << "------------------------------\n";

    mOst << "Processor Type : " << si.dwProcessorType << "\n";
    mOst << "Architecture : " << GetArchitectureString(si.wProcessorArchitecture) << "\n";

    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
    {
        mOst << "Processor Level (Family) : " << si.wProcessorLevel << "\n";
        mOst << "Revision : 0x"
            << std::hex << std::setw(4) << std::setfill('0')
            << si.wProcessorRevision
            << std::dec << std::setfill(' ') << "\n";
    }
    else
    {
        mOst << "Processor Level (Family) : unknown\n";
        mOst << "Revision : unknown\n";
    }

    mOst << "Number of (logical) Processors : " << si.dwNumberOfProcessors << "\n";
    mOst << "Features:\n";

    if (IsProcessorFeaturePresent(PF_PAE_ENABLED))
        mOst << "Physical Address Extension supported.\n";
    else
        mOst << "Physical Address Extension not supported.\n";

    if (IsProcessorFeaturePresent(PF_VIRT_FIRMWARE_ENABLED))
        mOst << "Virtualization enabled.\n";
    else
        mOst << "Virtualization not enabled.\n";
}

void ListSystemInfo::PrintSoftwareInfo()
{
    if (mOst.bad())
    {
        throw std::runtime_error(ERROR_BAD_OSTREAM);
    }

    char computerName[MAX_COMPUTERNAME_LENGTH + 1]{};
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;

    if (!GetComputerNameA(computerName, &size))
    {
        lstrcpyA(computerName, "unknown");
    }
    mOst << std::endl;
    mOst << "System Information <SOFTWARE>:\n";
    mOst << "------------------------------\n";
    mOst << "Computer Name: " << computerName << "\n";
    mOst << "OS Version : " << GetOSVersionString() << "\n";
    mOst << "Server : " << (IsWindowsServer() ? "Server Version" : "No Server Version") << "\n";
}



std::string ListSystemInfo::GetCmdName() const
{
	return std::string(ListSystemInfo::CMD_IDENTIFIER) + " -> List System Information (Usage: lss)";
}

std::string ListSystemInfo::GetCmdIdentifier() const
{
	return ListSystemInfo::CMD_IDENTIFIER;
}


