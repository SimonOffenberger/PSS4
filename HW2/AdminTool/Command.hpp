#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <memory>
#include <vector>

/**
 * @brief Base interface for executable commands in the AdminTool.
 */
class Command
{
public:

	using UPTR = std::unique_ptr<Command>;

	using TCont = std::vector<Command::UPTR>;

	/**
	 * @brief Executes the command with the provided argument.
	 * @param cmdArg Argument string required for command execution.
	 */
	virtual void Execute(const std::string& cmdArg) = 0;

	/**
	 * @brief Gets the full name and usage description of the command.
	 * @return A string containing the command name and usage.
	 */
	virtual std::string GetCmdName() const = 0;

	/**
	 * @brief Gets the raw identifier of the command used for invocation.
	 * @return The command identifier string.
	 */
	virtual std::string GetCmdIdentifier() const = 0;

	virtual ~Command() = default;
};

#endif


