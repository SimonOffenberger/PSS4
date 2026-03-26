#ifndef MENU_HPP
#define MENU_HPP

#include "Object.hpp"
#include "Command.hpp"
#include <iostream>


/**
 * @brief Manages a collection of commands and executes them.
 */
class Menu : public Object
{
public :

	inline static constexpr const char* ERROR_BAD_OSTREAM = "Error Bad Ostream Provided!";

	/**
	 * @brief Default constructor.
	 */
	Menu() = default;

	/**
	 * @brief Adds a new command to the menu.
	 * @param com Unique pointer to the command to add.
	 */
	void AddCommand(Command::UPTR com);

	/**
	 * @brief Displays the available menu commands to the given output stream.
	 * @param ost Output stream for display target.
	 */
	void ShowMenu(std::ostream & ost);

	/**
	 * @brief Executes a command by its identifier phrase.
	 * @param cmd The command line string (identifier + arguments).
	 */
	void ExecuteCommand(const std::string& cmd);

private:

	Command::TCont mCommands;
};

#endif // !MENU_HPP
