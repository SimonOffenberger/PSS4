#ifndef OPENAPP_HPP
#define OPENAPP_HPP

#include "Command.hpp"
#include "Object.hpp"

#include <string>

#include <iostream>

class OpenApp : public Command, public Object
{
public:
	OpenApp(std::istream& ins, std::ostream& out) : in{ ins }, ost{out} {}

	virtual void Execute() override;

	virtual std::string GetCmdName() const override;

	virtual std::string GetCmdIdentifier() const override;


private:

	std::istream & in;
	std::ostream & ost;

	inline static const std::string CMD_IDENTIFIER = "exec";

};

#endif