#include <gtest/gtest.h>
#include <string>
#include <parser_utils.h>

// Test basic addition
TEST(Parser, Plus)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1+1)", "Plus", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("2", output);
}

// Test basic multiplication
TEST(Parser, Multiply)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1*1)", "Multiply", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());

  EXPECT_EQ("1", output);
}

TEST(Parser, MultiplyAgain)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2*2)", "MultiplyAgain", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("4", output);
}

//
TEST(Parser, ShiftRight)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(">2", "ShiftRight", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("1", output);
}


TEST(Parser, ShiftLeft)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("<2", "ShiftLeft", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("4", output);
}

TEST(Parser, MalformedPlus)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("+2", "MalformedPlus", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MalformedPlusTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("2+", "MalformedPlusTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MalformedTimes)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("*2", "MalformedTimes", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MalformedTimesTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("2*", "MalformedTimesTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MalformedParentheses)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("((<123*234)", "MalformedParentheses", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MalformedParenthesesTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(<123*234))", "MalformedParenthesesTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ExtraTimes)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(*1138*3720)", "ExtraTimes", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ExtraTimesTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1138*3720*)", "ExtraTimes", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ExtraPlus)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(+1138*3720)", "ExtraPlus", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ExtraPlusTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1138*3720+)", "ExtraPlusTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MixingOperators)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1+2*3)", "MixingOperators", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MultiplePlusOperators)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1+2+3)", "MultiplePlusOperators", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("6", output);
}

TEST(Parser, MultipleTimesOperators)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2*2*3)", "MultipleTimesOperators", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("12", output);
}

// Simple test that uses all operators
TEST(Parser, MultipleOperatorsOne)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(<<14 *(>>123+333 ))", "MultipleOperatorsOne", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("20328", output);
}

TEST(Parser, MultipleOperatorsTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("<>(2 * 1* ( >500000000 + <<0))", "MultipleOperatorsTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("500000000", output);
}

// All expressions listed on assignment page
TEST(Parser, MultipleExpressions)
{
  std::string output;
  std::string expression =  "(<<14 *(>>123+333 ))\n"
                            "<>(2 * 1* ( >500000000 + <<0))\n"
                            "<>(1 * >3 * 3)\n"
                            "((<123*234)\n"
                            "(1337*9001+42)\n"
                            "(*1138*3720)";
  std::string expected =    "20328"
                            "500000000"
                            "2"
                            "Malformed"
                            "Malformed"
                            "Malformed";

  EXPECT_TRUE(runParserProgram(expression, "MultipleExpressions", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ(expected, output);
}
