#ifndef TERMINATEAPP_HPP
#define TERMINATEAPP_HPP

#include "Command.hpp"
#include "Object.hpp"
#include "windows.h"
#include <iostream>

/**
 * @brief Command to terminate an application by process ID.
 */
class TerminateApp : public Command, public Object
{
public:

	inline static constexpr const char* ERROR_TERMINATE_PROCESS_FAILED = "Failed to terminate process. Error: ";

	/**
	 * @brief Default constructor.
	 */
	TerminateApp() = default;

	/**
	 * @brief Executes the process termination command.
	 * @param cmdArg The process ID as a string.
	 */
	virtual void Execute(const std::string& cmdArg) override;

	/**
	 * @brief Gets the command name and usage.
	 * @return Command name and usage string.
	 */
	virtual std::string GetCmdName() const override;

	/**
	 * @brief Gets the command identifier.
	 * @return The identifier string.
	 */
	virtual std::string GetCmdIdentifier() const override;


private:

	inline static constexpr const char* CMD_IDENTIFIER = "term";
};

#endif