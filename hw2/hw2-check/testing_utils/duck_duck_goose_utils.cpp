#include <fstream>
#include <sstream>

#include <kwsys/SystemTools.hxx>

#include "duck_duck_goose_utils.h"

testing::AssertionResult runDuckDuckGooseProgram(unsigned int randomSeed, int itPlayerID, std::vector<int> otherPlayers, std::string testName, std::string & output)
{
	// set up file structure
	std::string executablePath = DDG_EXECUTABLE;
	std::string testFolder =  TEST_BINARY_DIR "/duck_duck_goose_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string configFilePath = testFolder + "/config.txt";
	std::string outputFilePath = testFolder + "/output.txt";

	// create config file
	{
		std::ofstream configFile(configFilePath);

		if(!configFile)
		{
			return testing::AssertionFailure() << "Couldn't create configuration file " << configFilePath;
		}

		configFile << randomSeed << std::endl;
		configFile << otherPlayers.size() + 1 << std::endl;
		configFile << itPlayerID << std::endl;
		for(int playerID : otherPlayers)
		{
			configFile << playerID << std::endl;
		}
	}

	// run the program
	UserCodeRunner ddgRunner(testFolder, executablePath, {configFilePath, outputFilePath}, true);
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

};