#include <fstream>
#include <sstream>

#include <kwsys/SystemTools.hxx>

#include "parser_utils.h"

testing::AssertionResult runParserProgram(std::string equation, std::string testName)
{
	// set up file structure
	std::string executablePath = PARSER_EXECUTABLE;
	std::string testFolder =  TEST_BINARY_DIR "/parser_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string configFilePath = testFolder + "/input.txt";

	// create input file
	{
		std::ofstream inputFile(inputFilePath);

		if(!inputFile)
		{
			return testing::AssertionFailure() << "Couldn't create input file " << inputFilePath;
		}

		inputFile << equation;
	}

	// run the program
	UserCodeRunner parserRunner(testFolder, executablePath, {inputFilePath}, true);
	testing::AssertionResult result = parserRunner.execute();

	if(!result)
	{
		return result;
	}

};
