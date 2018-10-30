//
// Class for running user programs and reading their output
//

#ifndef CS104_HW2_TEST_SUITE_USER_CODE_RUNNER_H
#define CS104_HW2_TEST_SUITE_USER_CODE_RUNNER_H

#include <string>
#include <vector>

#include<gtest/gtest.h>

#include <kwsys/Process.h>


class UserCodeRunner
{
	// prefix to a command needed to run it with Valgrind
	static const std::vector<std::string> valgrindCmd;

	// pointer to process structure
	kwsysProcess * _process;

	// executable path
	std::string _executablePath;

	// whether or not to write cout and cerr to the disk
	bool _saveStdout;

	// output file path -- is "" if _saveStdout is false
	std::string _outputFilePath;

	// working directory
	std::string _workingDirectory;

	// full command line as string for logging
	std::string _commandString;

	// sets the given command line for the cmsys process.
	// Called by both constructors.
	void setupCommandLine(std::string const & executablePath, std::vector<std::string> args, bool useValgrind);

public:

	// Construct a UserCodeRunner that saves output to a file.
	// Args:
	// outputFilePath - file to write output to
	// workingDirectory - folder to run program in
	// executablePath - path to user program executable
	// args - vector of command-line arguments to pass
	// useValgrind - whether or not to run the program inside valgrind
	UserCodeRunner(std::string const & workingDirectory, std::string const & executablePath, std::vector<std::string> args, std::string const & outputFilePath, bool useValgrind = true);

	// Construct a UserCodeRunner that does not save output.
	// Args:
	// outputFilePath - file to write output to
	// workingDirectory - folder to run program in
	// executablePath - path to user program executable
	// args - vector of command-line arguments to pass
	// useValgrind - whether or not to run the program inside valgrind
	UserCodeRunner(std::string const & workingDirectory, std::string const & executablePath, std::vector<std::string> args, bool useValgrind = true);

	// Run the user program, and wait until it finishes.
	// Returns an AssertionResult describing if and how the program failed.
	// To get detailed output, use it like this:
	// EXPECT_TRUE(runner.execute())
	testing::AssertionResult execute();

	~UserCodeRunner();

};

#endif //CS104_HW2_TEST_SUITE_USER_CODE_RUNNER_H
