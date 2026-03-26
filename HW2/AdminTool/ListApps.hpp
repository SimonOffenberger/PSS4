#ifndef LISTAPPS_HPP
#define LISTAPPS_HPP

#include "Command.hpp"
#include "Object.hpp"
#include "windows.h"
#include "tlhelp32.h"
#include <iostream>

/**
 * @brief Command to list running applications and their process information.
 */
class ListApps : public Command, public Object
{
public:

	inline static constexpr const char* ERROR_SNAPSHOT_FAILED = "Failed to create snapshot of processes. Error: ";
	inline static constexpr const char* ERROR_BAD_OSTREAM = "Output stream is in a bad state.";	

	inline static constexpr size_t cLowPrioThreshold = 4;
	inline static constexpr size_t cHighPrioThreshold = 10;
	/**
	 * @brief Constructor taking an output stream for printing.
	 * @param ost The output stream to print to.
	 */
	explicit ListApps(std::ostream& ost) : mOst{ ost } {}

	/**
	 * @brief Executes the process listing command.
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
	 * @brief Prints detailed information about a single process.
	 * @param entry The process entry to print.
	 */
	void PrintProcessInfo(const PROCESSENTRY32 & entry) const;

	/**
	 * @brief Prints the header for the process list.
	 */
	void PrintHeader() const;

	std::ostream & mOst;

	inline static constexpr size_t cProcessNameWidth = 40;
	inline static constexpr size_t cProcessPrioWidth = 15;
	inline static constexpr size_t cProcessPIDWidth = 10;
	inline static constexpr size_t cProcessCntTHWidth = 15;


	inline static constexpr const char* CMD_IDENTIFIER = "lsa";
};

#endif