

#include "OpenApp.hpp"
#include "TerminateApp.hpp"
#include "ListSystemInfo.hpp"
#include "vld.h"
#include "ListApps.hpp"
#include <iostream>
#include <conio.h>


int main(void)
{

	ListSystemInfo listSystemInfo{ std::cout };

	listSystemInfo.Execute();

	ListApps listApps{std::cout};

	listApps.Execute();

	OpenApp openApp("mspaint");

	openApp.Execute();

	DWORD appId = 0;

	std::cin >> appId;

	TerminateApp terminateApp(appId);

	terminateApp.Execute();

	_getch();

	return 0;
}
