//
// Created by cs104 on 7/24/18.
//

#include "user_code_runner.h"

#include "rang.h"

#include <iostream>
#include <sstream>

#include <kwsys/SystemTools.hxx>

const std::vector<std::string> UserCodeRunner::valgrindCmd{"/usr/bin/valgrind", "--tool=memcheck", "-q", "--leak-check=yes", "--error-exitcode=113"};

void UserCodeRunner::setupCommandLine(std::string const &executablePath, std::vector<std::string> args, bool useValgrind)
{
	// create odd C-array format needed by kwsysProcess
	std::vector<std::string> commandLineVector;

	if(useValgrind)
	{
		commandLineVector.insert(commandLineVector.begin(), valgrindCmd.begin(), valgrindCmd.end());
	}
	commandLineVector.push_back(executablePath);
	commandLineVector.insert(commandLineVector.end(), args.begin(), args.end());

	char const * * commandLine = new char const * [commandLineVector.size() + 1];

	for(size_t index = 0; index < commandLineVector.size(); ++index)
	{
		commandLine[index] = commandLineVector[index].c_str();
	}

	// null-terminate array
	commandLine[commandLineVector.size()] = nullptr;

	kwsysProcess_SetCommand(_process, commandLine);

	// delete outer array (inner memory is owned by the std::strings so it doesn't need to be deleted)
	delete[] commandLine;

	// make logging command line string
	std::stringstream cmdLineStream;
	bool firstLoop = true;
	for(std::string const & arg : commandLineVector)
	{
		if(firstLoop)
		{
			firstLoop = false;
		}
		else
		{
			cmdLineStream << ' ';
		}
		cmdLineStream << arg;
	}
	if(_saveStdout)
	{
		cmdLineStream << " > " << _outputFilePath;
	}

	_commandString = cmdLineStream.str();
}

UserCodeRunner::UserCodeRunner(std::string const & workingDirectory, std::string const & executablePath, std::vector<std::string> args, std::string const & outputFilePath, bool useValgrind):
	_process(kwsysProcess_New()),
	_executablePath(executablePath),
	_saveStdout(true),
	_outputFilePath(outputFilePath),
	_workingDirectory(workingDirectory)
{
	setupCommandLine(executablePath, args, useValgrind);

	// group cout and cerr
	kwsysProcess_SetOption(_process, kwsysProcess_Option_MergeOutput, 1);
}

UserCodeRunner::UserCodeRunner(std::string const & workingDirectory, std::string const & executablePath, std::vector<std::string> args, bool useValgrind):
_process(kwsysProcess_New()),
_executablePath(executablePath),
_saveStdout(false),
_outputFilePath(""),
_workingDirectory(workingDirectory)
{
	setupCommandLine(executablePath, args, useValgrind);
}

testing::AssertionResult UserCodeRunner::execute()
{
	// prepare process
	// -----------------------------------------------------------

	// make sure program exists
	if(!kwsys::SystemTools::FileExists(_executablePath))
	{
		// the CMake build system is supposed to run make before tests are executed, so this error message should make sense
		return testing::AssertionFailure() << "User program " << _executablePath << " does not exist after running make!";
	}

	if(_saveStdout)
	{
		// set output file
		kwsysProcess_SetPipeFile(_process, kwsysProcess_Pipe_STDOUT, _outputFilePath.c_str());
	}
	else
	{
		// print stdout and stderr to screen
		kwsysProcess_SetPipeShared(_process, kwsysProcess_Pipe_STDOUT, 1);
		kwsysProcess_SetPipeShared(_process, kwsysProcess_Pipe_STDERR, 1);
	}

	// set working directory
	if(!kwsys::SystemTools::FileIsDirectory(_workingDirectory))
	{
		return testing::AssertionFailure() << "Working directory (" << _workingDirectory << ") does not exist!";
	}
	kwsysProcess_SetWorkingDirectory(_process, _workingDirectory.c_str());

	// start process
	// -----------------------------------------------------------

	std::cout << "Executing program: " << rang::fgB::blue << _commandString << rang::fg::reset << std::endl;

	kwsysProcess_Execute(_process);
	kwsysProcess_WaitForExit(_process, nullptr);

	// analyze results
	// -----------------------------------------------------------

	kwsysProcess_State_e processState = static_cast<kwsysProcess_State_e>(kwsysProcess_GetState(_process));

	if(processState == kwsysProcess_State_Error)
	{
		return testing::AssertionFailure() << "User program could not be executed due to an error: " << kwsysProcess_GetErrorString(_process);
	}
	else if(processState == kwsysProcess_State_Killed)
	{
		return testing::AssertionFailure() << "User program was killed";
	}
	else if(processState == kwsysProcess_State_Exception)
	{
		return testing::AssertionFailure() << "User program crashed: " << kwsysProcess_GetExceptionString(_process);
	}

	int exitCode = kwsysProcess_GetExitValue(_process);

	if(exitCode == 113) // Valgrind exit code from command above
	{
		// the program did complete successfully, so we can continue with the test.  However, we need to report the Valgrind error to the graders
		std::cout << rang::fg::yellow << "WARNING: user program created Valgrind errors!" << rang::fg::reset << std::endl;
	}
	else if(exitCode != 0)
	{
		return testing::AssertionFailure() << "User program failed with nonzero exit code " << exitCode;
	}

	return testing::AssertionSuccess();
}

UserCodeRunner::~UserCodeRunner()
{
	kwsysProcess_Delete(_process);
}

