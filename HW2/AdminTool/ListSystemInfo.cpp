
#include "ListSystemInfo.hpp"
#include <windows.h>
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

static bool IsWindowsVersionOrGreater(WORD major, WORD minor)
{
    OSVERSIONINFOEXA osvi{};
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    osvi.dwMajorVersion = major;
    osvi.dwMinorVersion = minor;

    DWORDLONG mask = 0;
    VER_SET_CONDITION(mask, VER_MAJORVERSION, VER_GREATER_EQUAL);
    VER_SET_CONDITION(mask, VER_MINORVERSION, VER_GREATER_EQUAL);

    return VerifyVersionInfoA(&osvi, VER_MAJORVERSION | VER_MINORVERSION, mask) != FALSE;
}

static std::string GetOSVersionString()
{
    if (IsWindowsVersionOrGreater(10, 0))
        return "Windows 10 or greater";
    if (IsWindowsVersionOrGreater(6, 3))
        return "Windows 8.1 or greater";
    if (IsWindowsVersionOrGreater(6, 2))
        return "Windows 8 or greater";
    if (IsWindowsVersionOrGreater(6, 1))
        return "Windows 7 or greater";

    return "Older than Windows 7";
}

static bool IsServerOS()
{
    OSVERSIONINFOEXA osvi{};
    osvi.dwOSVersionInfoSize = sizeof(osvi);

    DWORDLONG mask = 0;
    VER_SET_CONDITION(mask, VER_PRODUCT_TYPE, VER_EQUAL);

    osvi.wProductType = VER_NT_WORKSTATION;

    return VerifyVersionInfoA(&osvi, VER_PRODUCT_TYPE, mask) == FALSE;
}

void ListSystemInfo::Execute()
{
	PrintHardwareInfo();
	PrintSoftwareInfo();
}

void ListSystemInfo::PrintHardwareInfo()
{
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
    char computerName[MAX_COMPUTERNAME_LENGTH + 1]{};
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;

    if (!GetComputerNameA(computerName, &size))
    {
        lstrcpyA(computerName, "unknown");
    }

    mOst << "System Information <SOFTWARE>:\n";
    mOst << "------------------------------\n";
    mOst << "Computer Name: " << computerName << "\n";
    mOst << "OS Version : " << GetOSVersionString() << "\n";
    mOst << "Server : " << (IsServerOS() ? "Server Version" : "No Server Version") << "\n";
}



std::string ListSystemInfo::GetCmdName() const
{
	return "List System Information";
}

