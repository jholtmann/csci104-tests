#include <duck_duck_goose_utils.h>
#include <random_generator.h>
#include <duck_duck_goose.h>
#include <gtest/gtest.h>

/* ################## BEGIN BASIC TESTS ############# */

// first we have a simple test of simulateDDGRound().
// Keep in mind that there are only two outcomes with two players, so we can just test for each one.  This won't be the case when we add more players!
// If you want, you can reuse the first half of the function in other tests, and just compare against
// a static string in your code.  Remember that as long as you use the same argument to srand(), your
// code will produce the same output for the same input.
TEST(DDGRoundBasic, TwoPlayers)
{
	srand(94785);

	GameData testData;
	testData.itPlayerID = 701;
	testData.playerList.push_back(8);

	std::stringstream roundOutputStream;

	simulateDDGRound(&testData, roundOutputStream);

	std::string roundOutput = roundOutputStream.str();

	// two possibilities
	if(roundOutput.find("701 took 8's spot") != std::string::npos)
	{
		EXPECT_EQ(testData.playerList.size(), 1);
		EXPECT_EQ(testData.itPlayerID, 8);
	}
	else if(roundOutput.find("701 is out!") != std::string::npos)
	{
		EXPECT_EQ(testData.playerList.size(), 1);
		EXPECT_EQ(testData.itPlayerID, 0);
	}
	else
	{
		// unrecognized output
		FAIL();
	}
}

// This test actually invokes your program on the command line.
// We are giving you runDuckDuckGooseProgram() in ../testing_utils/duck_duck_goose_utils.h,
// which takes care of writing the configuration file, executing your program, and reading the results.
TEST(DDGBasic, FivePlayers)
{
	const unsigned int randomSeed = 47;
	const int itPlayerID = 2;
	const std::vector<int> otherPlayers = {8, 953, 4, 200, 68};
	const std::string testName = "basic_five_players";
	std::string output;

	//NOTE: the output of running your program will be written to the file hw2-check/duck_duck_goose_tests/testFiles/testName
	ASSERT_TRUE(runDuckDuckGooseProgram(randomSeed, itPlayerID, otherPlayers, testName, output));

	// if we got here, then your program executed successfully and passed Valgriund, which is great!
	// now, it's up to you to do something useful with the output.
}

/* ################## END BASIC TESTS ################## */
