#include <duck_duck_goose_utils.h>
#include <random_generator.h>
#include <duck_duck_goose.h>
#include <gtest/gtest.h>

/* 	AUTHOR: JONATHAN HOLTMANN
		EMAIL: holtmann@usc.edu
		DESCIPTION: The following contains extra test cases for the CSCI 104
								homework assignment nr. 2
*/

TEST(DDGRoundBasic, ScricterTwoPlayers) {
	srand(94785);

	GameData testData;
	testData.itPlayerID = 701;
	testData.playerList.push_back(8);

	std::stringstream roundOutputStream;

	simulateDDGRound(&testData, roundOutputStream);

	std::string roundOutput = roundOutputStream.str();

	// Check to make sure program output matches expected output exactly
	if(roundOutput.find("8 is a Duck.") == std::string::npos ||
			roundOutput.find("8 is a Goose!") == std::string::npos) {
		FAIL();
	}

	if(roundOutput.find("701 took 8's spot") != std::string::npos) {
		EXPECT_EQ(testData.playerList.size(), 1);
		EXPECT_EQ(testData.itPlayerID, 8);
	} else if(roundOutput.find("701 is out!") != std::string::npos) {
		EXPECT_EQ(testData.playerList.size(), 1);
		EXPECT_EQ(testData.itPlayerID, 0);
	} else {
		FAIL();
	}
}

// DDGRound should produce the same output every time if a seed is set
TEST(DDGRoundJTest, SeedTest) {
	int prev_id;
	for (int i = 0; i < 10; i++) {
		srand(12345);
		GameData testData;
		testData.itPlayerID = 200;
		testData.playerList.push_back(8);
		std::stringstream roundOutputStream;

		simulateDDGRound(&testData, roundOutputStream);

		if (i != 0)
			EXPECT_EQ(prev_id, testData.itPlayerID);
		prev_id = testData.itPlayerID;
	}

}

TEST(DDGRoundJTest, MultiRoundTest)
{
	srand(12345);

	GameData testData;
	testData.itPlayerID = 200;
	std::vector<int> players = {8,14,1,231,76,168};

	for (int p : players) {
		testData.playerList.push_back(p);
	}

	// int r = 0;
	while(testData.itPlayerID != 0) {
		// std::cerr << "Round " << ++r << std::endl;
		std::stringstream roundOutputStream;

		simulateDDGRound(&testData, roundOutputStream);

		std::string roundOutput = roundOutputStream.str();

		// std::cerr << roundOutput << std::endl;
	}

	EXPECT_EQ(1, testData.playerList.size());
	EXPECT_EQ(0, testData.itPlayerID);
}
