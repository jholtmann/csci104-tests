#include <fstream>
#include <sstream>
#include <string>

#include <kwsys/SystemTools.hxx>

#include "parser_utils.h"

testing::AssertionResult runParserProgram(std::string equation, std::string testName, std::string &output)
{
	// set up file structure
	std::string executablePath = PARSER_EXECUTABLE;
	std::string testFolder = std::string(TEST_BINARY_DIR) + "/parser_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";

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
	UserCodeRunner parserRunner(testFolder, executablePath, {inputFilePath}, outputFilePath, false);
	testing::AssertionResult result = parserRunner.execute();

	if(!result)
	{
		return result;
	}

	// read output
	{
		std::ifstream outputFile(outputFilePath);

		if(!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}

		std::stringstream outputFileContents;
		outputFileContents << outputFile.rdbuf();

		output = outputFileContents.str();
		return testing::AssertionSuccess();
	}

};
