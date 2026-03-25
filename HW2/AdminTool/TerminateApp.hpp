#ifndef TERMINATEAPP_HPP
#define TERMINATEAPP_HPP

#include "Command.hpp"
#include "Object.hpp"
#include "windows.h"

class TerminateApp : public Command, public Object
{
public:
    TerminateApp(const DWORD app);

	virtual void Execute() override;

	virtual std::string GetCmdName() const override;

	virtual std::string GetCmdIdentifier() const override;


private:

	inline static const std::string CMD_IDENTIFIER = "term";


	DWORD mApp;
};

#endif