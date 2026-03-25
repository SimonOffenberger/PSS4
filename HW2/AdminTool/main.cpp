

#include "OpenApp.hpp"
#include "TerminateApp.hpp"
#include "ListSystemInfo.hpp"
#include "vld.h"
#include "ListApps.hpp"
#include "Menu.hpp"
#include <iostream>
#include <conio.h>


int main(void)
{


	Menu menu;
	menu.AddCommand(std::move(std::make_unique<ListApps>(std::cout)));
	menu.AddCommand(std::move(std::make_unique<TerminateApp>(120)));
	menu.AddCommand(std::move(std::make_unique<OpenApp>(std::cin,std::cout)));
	menu.AddCommand(std::move(std::make_unique<ListSystemInfo>(std::cout)));

	menu.ShowMenu(std::cout);

	std::string input = "";

	while (true) {
		std::cout << ">";
		std::cin >> input;
		menu.ExecuteCommand(input);
	}

	_getch();

	return 0;
}
