#ifndef MENU_HPP
#define MENU_HPP

#include "Object.hpp"
#include "Command.hpp"
#include <iostream>


class Menu : public Object
{
public :

	inline static const std::string ERROR_BAD_OSTREAM = "Error Bad Ostream Provided!";

	Menu() = default;

	void AddCommand(Command::UPTR com);
	void ShowMenu(std::ostream & ost);
	void ExecuteCommand(const std::string& cmd);

private:

	Command::TCont mCommands;
};



#endif // !MENU_HPP
