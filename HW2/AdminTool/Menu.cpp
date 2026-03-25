#include "Menu.hpp"
#include <cassert>
#include <algorithm>

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
	const auto & find = std::find_if(mCommands.cbegin(), mCommands.cend(), [&](const Command::UPTR & com) {
		return com->GetCmdIdentifier() == cmd;
	});

	if(find != mCommands.cend())
	{
		(*find)->Execute();
	}
	else
	{
		std::cerr << "Unknown Command: " << cmd << std::endl;
	}
}
