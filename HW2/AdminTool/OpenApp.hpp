#ifndef OPENAPP_HPP
#define OPENAPP_HPP

#include "Command.hpp"
#include "Object.hpp"

#include <string>

class OpenApp : public Command, public Object
{
public:
    OpenApp(const std::string & app);

	virtual void Execute() override;

	virtual std::string GetCmdName() const override;

private:
	std::string mApp;
};

#endif