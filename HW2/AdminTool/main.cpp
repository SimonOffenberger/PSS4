
#include <fstream>
#include "OpenApp.hpp"
#include "TerminateApp.hpp"
#include "ListSystemInfo.hpp"
#include "vld.h"
#include "ListApps.hpp"
#include "Menu.hpp"
#include <sstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
#include "Test.hpp"

#define WriteOutputFile ON
#define STR_EQUAL 0

using namespace std;

static bool TestListApps(ostream& ost);
static bool TestSystemInfo(ostream& ost);
static bool TestOpenApp(ostream& ost);
static bool TestTerminateApp(ostream& ost);
static bool TestMenu(ostream& ost);

static std::set<DWORD> GetProcessIdsByName(const std::string& exeName);
static bool ContainsProcessId(const std::set<DWORD>& pids, DWORD pid);


int main(void)
{

    ofstream output{ "Testoutput.txt" };

    if (!output.is_open()) {
        cerr << "Konnte Testoutput.txt nicht oeffnen" << TestCaseFail;
        return 1;
    }

    try {

		bool TestOK = true;


		TestOK = TestOK && TestListApps(cout);
		TestOK = TestOK && TestSystemInfo(cout);
		TestOK = TestOK && TestOpenApp(cout);
		TestOK = TestOK && TestTerminateApp(cout);
		TestOK = TestOK && TestMenu(cout);


        if (WriteOutputFile) {

		TestOK = TestOK && TestListApps(output);
		TestOK = TestOK && TestSystemInfo(output);
		TestOK = TestOK && TestOpenApp(output);
		TestOK = TestOK && TestTerminateApp(output);
		TestOK = TestOK && TestMenu(output);



            if (TestOK) {
                output << TestCaseOK;
            }
            else {
                output << TestCaseFail;
            }

            output.close();
        }

        if (TestOK) {
            cout << TestCaseOK;
        }
        else {
            cout << TestCaseFail;
        }
    }
    catch (const string& err) {
        cerr << err << TestCaseFail;
    }
    catch (bad_alloc const& error) {
        cerr << error.what() << TestCaseFail;
    }
    catch (const exception& err) {
        cerr << err.what() << TestCaseFail;
    }
    catch (...) {
        cerr << "Unhandelt Exception" << TestCaseFail;
    }

    if (output.is_open()) output.close();

	try {
		Menu menu;
		menu.AddCommand(move(make_unique<ListApps>(cout)));
		menu.AddCommand(move(make_unique<TerminateApp>()));
		menu.AddCommand(move(make_unique<OpenApp>()));
		menu.AddCommand(move(make_unique<ListSystemInfo>(cout)));

		menu.ShowMenu(cout);

		string input = "";
		cout << "Enter a command (or 'exit' to quit):" << endl;
		while (input != "exit") {
			cout << ">";

			getline(cin >> ws, input); // read the rest of the line without leading whitespace

			if (input != "exit") {
				menu.ExecuteCommand(input);
			}
		}
	}
	catch (...) {
		cerr << "An unexpected error occurred. Exiting." << endl;
	}

	return 0;
}

bool TestListApps(ostream& ost)
{
	assert(ost.good());

	bool TestOK = true;
	string error_msg = "";

	try {

		ListApps listAppsCmd(ost);

		const string CMD_ID = "lsa";

		TestOK = TestOK && check_dump(ost, "Test Cmd Identifier", CMD_ID, listAppsCmd.GetCmdIdentifier());

		ost << "--------------------------" << std::endl;
		ost << "Executing ListApps Command..." << std::endl;
		listAppsCmd.Execute("");
		ost << "--------------------------" << std::endl;

	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception in TestCase", true, error_msg.empty());
	error_msg.clear();

	try {
		stringstream bad_ost;
		bad_ost.setstate(ios::failbit); // set the failbit to simulate a bad ostream

		ListApps listAppsCmd(bad_ost);

		listAppsCmd.Execute("");
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception Error Bad Ost", STR_EQUAL,strcmp(error_msg.c_str(), ListApps::ERROR_BAD_OSTREAM));
	error_msg.clear();

	return TestOK;
}

bool TestTerminateApp(ostream& ost)
{
	assert(ost.good());

	bool TestOK = true;
	string error_msg = "";

	try {
		TerminateApp termCmd;

		const string CMD_ID = "term";
		TestOK = TestOK && check_dump(ost, "Test Cmd Identifier", CMD_ID, termCmd.GetCmdIdentifier());
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception in TestCase", true, error_msg.empty());
	error_msg.clear();

	try {
		const auto before = GetProcessIdsByName("mspaint.exe");

		OpenApp openAppCmd;
		openAppCmd.Execute("mspaint");
		Sleep(750);

		const auto after = GetProcessIdsByName("mspaint.exe");
		std::vector<DWORD> newPids;
		for (DWORD pid : after)
		{
			if (!ContainsProcessId(before, pid))
			{
				newPids.push_back(pid);
			}
		}

		TestOK = TestOK && check_dump(ost, "TerminateApp setup: mspaint started", true, !newPids.empty());

		if (!newPids.empty())
		{
			TerminateApp termCmd;
			termCmd.Execute(std::to_string(newPids.front()));
			Sleep(750);

			const auto afterTerminate = GetProcessIdsByName("mspaint.exe");
			TestOK = TestOK && check_dump(ost, "TerminateApp terminated mspaint", false, ContainsProcessId(afterTerminate, newPids.front()));
		}
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception in terminate flow", true, error_msg.empty());
	error_msg.clear();

	try {
		TerminateApp termCmd;
		termCmd.Execute("0");
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "TerminateApp throws for invalid PID", false, error_msg.empty());
	error_msg.clear();

	try {
		TerminateApp termCmd;
		termCmd.Execute("abc"); // converts to 0
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "TerminateApp throws for non-numeric PID", false, error_msg.empty());
	error_msg.clear();

	return TestOK;
}

bool TestMenu(ostream& ost)
{
	assert(ost.good());

	bool TestOK = true;
	string error_msg = "";

	class DummyCommand : public Command
	{
	public:
		void Execute(const std::string& cmdArg) override
		{
			mExecuted = true;
			mLastArg = cmdArg;
		}

		std::string GetCmdName() const override
		{
			return std::string(GetCmdIdentifier()) + " -> Dummy (Usage: dmy <args>)";
		}

		std::string GetCmdIdentifier() const override
		{
			return "dmy";
		}

		bool mExecuted = false;
		std::string mLastArg;
	};

	try {
		Menu menu;
		auto dummy = std::make_unique<DummyCommand>();
		auto* dummyPtr = dummy.get();
		menu.AddCommand(std::move(dummy));

		std::stringstream out;
		menu.ShowMenu(out);

		const std::string menuText = out.str();
		TestOK = TestOK && check_dump(ost, "Menu::ShowMenu contains command identifier", true, menuText.find("dmy") != std::string::npos);
		TestOK = TestOK && check_dump(ost, "Menu::ShowMenu contains usage text", true, menuText.find("Usage") != std::string::npos);

		menu.ExecuteCommand("dmy arg1 arg2");
		TestOK = TestOK && check_dump(ost, "Menu::ExecuteCommand calls Execute", true, dummyPtr->mExecuted);
		TestOK = TestOK && check_dump(ost, "Menu::ExecuteCommand passes arguments", std::string("arg1 arg2"), dummyPtr->mLastArg);

		dummyPtr->mExecuted = false;
		dummyPtr->mLastArg.clear();
		menu.ExecuteCommand("unknown something");
		TestOK = TestOK && check_dump(ost, "Menu::ExecuteCommand ignores unknown commands", false, dummyPtr->mExecuted);
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception in TestCase", true, error_msg.empty());
	error_msg.clear();

	try {
		Menu menu;
		std::stringstream bad_ost;
		bad_ost.setstate(ios::failbit);
		menu.ShowMenu(bad_ost);
	}
	catch (const std::runtime_error& err) {
		error_msg = err.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Menu::ShowMenu throws on bad ostream", STR_EQUAL, strcmp(error_msg.c_str(), Menu::ERROR_BAD_OSTREAM));
	error_msg.clear();

	return TestOK;
}

bool TestSystemInfo(ostream& ost)
{
	assert(ost.good());

	bool TestOK = true;
	string error_msg = "";

	try {

		ListSystemInfo listSysCmd(ost);

		const string CMD_ID = "lss";

		TestOK = TestOK && check_dump(ost, "Test Cmd Identifier", CMD_ID, listSysCmd.GetCmdIdentifier());

		ost << "--------------------------" << std::endl;
		ost << "Executing ListSysInfo Command..." << std::endl;
		listSysCmd.Execute("");
		ost << "--------------------------" << std::endl;

	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception in TestCase", true, error_msg.empty());
	error_msg.clear();

	try {
		stringstream bad_ost;
		bad_ost.setstate(ios::failbit); // set the failbit to simulate a bad ostream

		ListSystemInfo listSysCmd(bad_ost);

		listSysCmd.Execute("");
	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception Error Bad Ost", STR_EQUAL, strcmp(error_msg.c_str(), ListSystemInfo::ERROR_BAD_OSTREAM));
	error_msg.clear();

	return TestOK;
}

bool TestOpenApp(ostream& ost)
{
	assert(ost.good());

	bool TestOK = true;
	string error_msg = "";

	try {
		OpenApp openAppCmd;

		const string CMD_ID = "exec";
		TestOK = TestOK && check_dump(ost, "Test Cmd Identifier", CMD_ID, openAppCmd.GetCmdIdentifier());

		const auto before = GetProcessIdsByName("mspaint.exe");

		ost << "--------------------------" << std::endl;
		ost << "Executing OpenApp Command (mspaint)..." << std::endl;
		openAppCmd.Execute("mspaint");
		ost << "--------------------------" << std::endl;

		Sleep(750);
		const auto after = GetProcessIdsByName("mspaint.exe");

		std::vector<DWORD> newPids;
		newPids.reserve(after.size());
		for (DWORD pid : after)
		{
			if (!ContainsProcessId(before, pid))
			{
				newPids.push_back(pid);
			}
		}

		TestOK = TestOK && check_dump(ost, "OpenApp started a new mspaint process", true, !newPids.empty());

		if (!newPids.empty())
		{
			TerminateApp termCmd;
			termCmd.Execute(std::to_string(newPids.front()));
			Sleep(750);

			const auto afterTerminate = GetProcessIdsByName("mspaint.exe");
			TestOK = TestOK && check_dump(ost, "TerminateApp closed mspaint", false, ContainsProcessId(afterTerminate, newPids.front()));
		}

	}
	catch (const string& err) {
		error_msg = err;
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception in TestCase", true, error_msg.empty());
	error_msg.clear();

	try {
		OpenApp openAppCmd;
		openAppCmd.Execute("");
	}
	catch (const std::invalid_argument& err) {
		error_msg = err.what();
	}
	catch (const std::exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

	TestOK = TestOK && check_dump(ost, "Test Exception for empty command", false, error_msg.empty());
	error_msg.clear();

	try {
       OpenApp openAppCmd;
		openAppCmd.Execute("__this_application_should_not_exist__");
	}
 catch (const std::runtime_error& err) {
		error_msg = err.what();
	}
	catch (bad_alloc const& error) {
		error_msg = error.what();
	}
	catch (const exception& err) {
		error_msg = err.what();
	}
	catch (...) {
		error_msg = "Unhandelt Exception";
	}

    TestOK = TestOK && check_dump(ost, "Test Exception for invalid app", false, error_msg.empty());
	error_msg.clear();

	return TestOK;
}

static std::set<DWORD> GetProcessIdsByName(const std::string& exeName)
{
	std::set<DWORD> pids;

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return pids;
	}

	PROCESSENTRY32 entry{};
	entry.dwSize = sizeof(entry);

	BOOL ok = Process32First(hProcessSnap, &entry);
	while (ok)
	{
		if (exeName == entry.szExeFile)
		{
			pids.insert(entry.th32ProcessID);
		}
		ok = Process32Next(hProcessSnap, &entry);
	}

	CloseHandle(hProcessSnap);
	return pids;
}

static bool ContainsProcessId(const std::set<DWORD>& pids,DWORD pid)
{
	return pids.find(pid) != pids.end();
}
