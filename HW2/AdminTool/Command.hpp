#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <memory>
#include <vector>

class Command
{
public:

	using UPTR = std::unique_ptr<Command>;

	using TCont = std::vector<Command::UPTR>;

	virtual void Execute() = 0;	

	virtual std::string GetCmdName() const = 0;

	virtual std::string GetCmdIdentifier() const = 0;

    virtual ~Command() = default;
};

#endif


