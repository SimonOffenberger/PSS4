// -----------------------------------------------------------
// Implementation of simple helper functions
// HSD / FH-Hagenberg
// -----------------------------------------------------------

#include "Hlp.h"


// -----------------------------------------------------------
// print a windows error as human readable string
// usage:  cout << "Error: " << ErrMsg(GetLastError()) << endl;
std::string Hlp::ErrMsg(DWORD LastError) {
	LPVOID lpMsgBuf = nullptr;
	const DWORD len = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		0,
		LastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		reinterpret_cast<LPSTR>(&lpMsgBuf),
		0,
		0
	);

	if (len == 0 || lpMsgBuf == nullptr) {
		return "Unknown error code: " + std::to_string(LastError);
	}

	std::string ErrStr(static_cast<char*>(lpMsgBuf));
	// Free the buffer.
	LocalFree(lpMsgBuf);

	return ErrStr;
}
