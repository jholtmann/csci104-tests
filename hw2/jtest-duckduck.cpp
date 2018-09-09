#include <duck_duck_goose_utils.h>
#include <random_generator.h>
#include <duck_duck_goose.h>
#include <gtest/gtest.h>

/* 	AUTHOR: JONATHAN HOLTMANN
		EMAIL: holtmann@usc.edu
		DESCIPTION: The following contains extra test cases for the CSCI 104
								homework assignment nr. 2/
*/

TEST(DDGRoundJTest, SecondTwoPlayerTest)
{
	srand(12345);

	GameData testData;
	testData.itPlayerID = 220;
	testData.playerList.push_back(8);

	std::stringstream roundOutputStream;

	simulateDDGRound(&testData, roundOutputStream);

	std::string roundOutput = roundOutputStream.str();

	std::cerr << roundOutput << std::endl;

	EXPECT_EQ(testData.playerList.size(), 1);

	// two possibilities
	if(roundOutput.find("220 took 8's spot") != std::string::npos)
	{
		EXPECT_EQ(testData.itPlayerID, 8);
	}
	else if(roundOutput.find("220 is out!") != std::string::npos)
	{
		EXPECT_EQ(testData.itPlayerID, 0);
	}
	else
	{
		// unrecognized output
		FAIL();
	}
}
