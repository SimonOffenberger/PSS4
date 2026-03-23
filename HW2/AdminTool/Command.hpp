#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>


class Command
{
public:

	virtual void Execute() = 0;	

	virtual std::string GetCmdName() const = 0;

    virtual ~Command() = default;
};

#endif


