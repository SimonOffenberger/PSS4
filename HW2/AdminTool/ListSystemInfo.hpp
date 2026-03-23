#ifndef LISTSYSTEMINFO_HPP
#define LISTSYSTEMINFO_HPP

#include "Command.hpp"
#include "Object.hpp"
#include <windows.h>
#include <iostream>

class ListSystemInfo :public Command, public Object
{
public:

	ListSystemInfo(std::ostream & ost) : mOst{ ost } {}

	virtual void Execute() override;

	virtual std::string GetCmdName() const override;

private:

	void PrintSoftwareInfo();
	void PrintHardwareInfo();

	std::ostream& mOst;
};

#endif