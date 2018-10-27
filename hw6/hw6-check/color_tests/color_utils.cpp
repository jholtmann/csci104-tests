#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

#include <user_code_runner.h>
#include <kwsys/SystemTools.hxx>

#include "color_utils.h"

using namespace std;

testing::AssertionResult runColor(string & output, string testName, int letters, int rows, int cols, string map) {
	// set up file structure
	std::string executablePath = USER_CODE_DIR "/coloring";
	std::string testFolder =  TEST_BINARY_DIR "/color_tests/test_files/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string configFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";

	// create config file
	{
		ofstream configFile(configFilePath);

		if(!configFile)
		{
			return testing::AssertionFailure() << "Couldn't create configuration file " << configFilePath;
		}

    configFile << letters << " " << rows << " " << cols << endl;
    configFile << map;
	}

	// run the program
	UserCodeRunner ddgRunner(testFolder, executablePath, {configFilePath}, outputFilePath, true);
	testing::AssertionResult result = ddgRunner.execute();

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
}
