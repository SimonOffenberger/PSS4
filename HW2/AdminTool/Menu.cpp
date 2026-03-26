#include "Menu.hpp"
/**
 * @file Menu.cpp
 * @brief Implementation of the Menu class.
 */
#include "Menu.hpp"
#include <cassert>
#include <algorithm>
#include <sstream>

static std::ostream & hline(std::ostream & os)
{	
	assert(os.good());	

	return os << "----------------------------------------" << std::endl;
}



void Menu::AddCommand(Command::UPTR com)
{
	mCommands.push_back(std::move(com));
}

void Menu::ShowMenu(std::ostream& ost)
{
	if(ost.fail())
	{
		throw std::runtime_error(ERROR_BAD_OSTREAM);
	}

	ost << hline;
	ost << "Available Commands: " << std::endl;

	size_t num = 0;

	std::for_each(mCommands.cbegin(),mCommands.cend(),[&](const auto & cmd)
	{
		ost << num++ << " " << cmd->GetCmdName() << std::endl;
	});
}

void Menu::ExecuteCommand(const std::string & cmd)
{

	std::stringstream converter;

	converter << cmd;

	std::string cmdIdentifier;
	// extract the first word of the command as identifier
	converter >> cmdIdentifier;

	const auto & find = std::find_if(mCommands.cbegin(), mCommands.cend(), [&](const Command::UPTR & com) {
		return com->GetCmdIdentifier() == cmdIdentifier;
	});

	try {

		if (find != mCommands.cend())
		{
			std::string cmdArg;
			// extract the rest of the command as argument
			std::getline(converter >> std::ws, cmdArg); // read the rest of the line without leading whitespace
			(*find)->Execute(cmdArg);
		}
		else
		{
			std::cerr << "Unknown Command: " << cmd << std::endl;
		}
	}
	catch (const std::exception & ex)
	{
		std::cerr << "Error executing command: " << ex.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error executing command: " << cmd << std::endl;
	}
}
