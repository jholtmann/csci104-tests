#include <duck_duck_goose_utils.h>
#include <random_generator.h>
#include <duck_duck_goose.h>
#include <gtest/gtest.h>

/* 	AUTHOR: JONATHAN HOLTMANN
		EMAIL: holtmann@usc.edu
		DESCIPTION: The following contains extra test cases for the CSCI 104
								homework assignment nr. 2/
*/

TEST(DDGRoundJTest, TwoPlayersNegativeIDs)
{
	srand(12345);

	GameData testData;
	testData.itPlayerID = -701;
	testData.playerList.push_back(-8);

	std::stringstream roundOutputStream;

	simulateDDGRound(&testData, roundOutputStream);

	std::string roundOutput = roundOutputStream.str();

	std::cerr << roundOutput << std::endl;

	EXPECT_EQ(testData.playerList.size(), 1);

	// two possibilities
	if(roundOutput.find("-701 took -8's spot") != std::string::npos)
	{
		EXPECT_EQ(testData.itPlayerID, -8);
	}
	else if(roundOutput.find("-701 is out!") != std::string::npos)
	{
		EXPECT_EQ(testData.itPlayerID, 0);
	}
	else
	{
		// unrecognized output
		FAIL();
	}
}

// Checks to make sure seed is being set correctly
TEST(DDGRoundJTest, CheckRand) {
	srand(12345);

	GameData testData;
	testData.itPlayerID = -701;
	testData.playerList.push_back(-8);

	std::stringstream roundOutputStream;

	simulateDDGRound(&testData, roundOutputStream);

	std::string roundOutput = roundOutputStream.str();

	std::cerr << roundOutput << std::endl;

	EXPECT_EQ(testData.playerList.size(), 1);

	if(roundOutput.find("-701 took -8's spot") != std::string::npos)
	{
		EXPECT_EQ(testData.itPlayerID, -8);
	} else {
		FAIL();
	}
}

// TEST(DDGBasicJTest, PlayerZeroIt)
// {
// 	const unsigned int randomSeed = 47;
// 	const int itPlayerID = 0;
// 	const std::vector<int> otherPlayers = {8, 953, 4, 200, 68};
// 	const std::string testName = "basic_five_players";
// 	std::string output;
//
// 	//NOTE: the output of running your program will be written to the file hw2-check/duck_duck_goose_tests/testFiles/testName
// 	ASSERT_TRUE(runDuckDuckGooseProgram(randomSeed, itPlayerID, otherPlayers, testName, output));
//
// 	// if we got here, then your program executed successfully and passed Valgriund, which is great!
// 	// now, it's up to you to do something useful with the output.
// }
