#ifndef LISTSYSTEMINFO_HPP
#define LISTSYSTEMINFO_HPP

#include "Command.hpp"
#include "Object.hpp"
#include <windows.h>
#include <iostream>

/**
 * @brief Command to list system hardware and software information.
 */
class ListSystemInfo : public Command, public Object
{
public:

	inline static constexpr const char* ERROR_BAD_OSTREAM = "Output stream is in a bad state.";

	/**
	 * @brief Constructor taking an output stream for printing.
	 * @param ost The output stream to print to.
	 */
	explicit ListSystemInfo(std::ostream & ost) : mOst{ ost } {}

	/**
	 * @brief Executes the system info listing command.
	 * @param cmdArg Command arguments (ignored).
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

	/**
	 * @brief Prints software information of the system.
	 */
	void PrintSoftwareInfo();

	/**
	 * @brief Prints hardware information of the system.
	 */
	void PrintHardwareInfo();

	std::ostream& mOst;

	inline static constexpr const char* CMD_IDENTIFIER = "lss";
};

#endif