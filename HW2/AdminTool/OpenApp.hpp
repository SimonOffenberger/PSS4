#ifndef OPENAPP_HPP
#define OPENAPP_HPP

#include "Command.hpp"
#include "Object.hpp"

#include <string>

#include <iostream>

/**
 * @brief Command to open an external application.
 */
class OpenApp : public Command, public Object
{
public:

	inline static constexpr const char* ERROR_CREATE_PROCESS_FAILED = "Failed to create process. Error: ";


	/**
	 * @brief Default constructor.
	 */
	OpenApp() = default;

	/**
	 * @brief Executes the open application command.
	 * @param cmdArg The application name or path to execute.
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

	inline static constexpr const char* CMD_IDENTIFIER = "exec";

};

#endif