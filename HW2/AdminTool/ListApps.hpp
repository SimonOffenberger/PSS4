#ifndef LISTAPPS_HPP
#define LISTAPPS_HPP

#include "Command.hpp"
#include "Object.hpp"
#include "windows.h"
#include "tlhelp32.h"
#include <iostream>

class ListApps :public Command , public Object
{
public:
	ListApps(std::ostream& ost) : mOst{ ost } {}

	virtual void Execute() override;

	virtual std::string GetCmdName() const override;

private:

	void PrintProcessInfo(const PROCESSENTRY32 & entry) const;

	void PrintHeader() const;

	std::ostream & mOst;

	inline static const size_t cProcessNameWidth = 40;
	inline static const size_t cProcessPrioWidth = 15;
	inline static const size_t cProcessPIDWidth = 10;
	inline static const size_t cProcessCntTHWidth = 15;


};

#endif