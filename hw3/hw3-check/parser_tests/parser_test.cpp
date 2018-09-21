#include <gtest/gtest.h>
#include <parser_utils.h>

#include <algorithm>
#include <string>

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

TEST(Parser, ShiftComplex)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(<2 + <9)", "ShiftLeft", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("22", output);
}

TEST(Parser, ShiftRightNoValue)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(">", "ShiftRightNoValue", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ShiftLeftNoValue)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("<", "ShiftLeftNoValue", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ShiftParentheses)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(<2)", "ShiftParentheses", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ShiftRightSide)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2>)", "ShiftRightSide", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ShiftRightSideTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2< + 7)", "ShiftRightSideTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, JustANumber)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("2", "JustANumber", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("2", output);
}

TEST(Parser, JustANumberParentheses)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2)", "JustANumberParentheses", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
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

TEST(Parser, ParenthesMiddle)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( (>2 + (3*3) ) * 3 )", "ParenthesMiddle", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("30", output);
}

TEST(Parser, ParenthesMiddleTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( (<2 + (3+3) ) * 3 )", "ParenthesMiddleTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("30", output);
}

TEST(Parser, ParenthesMiddleAdd)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 + (3 + 3) + 3 )", "ParenthesMiddleAdd", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("11", output);
}

TEST(Parser, ParenthesMiddleMultiply)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 * (3 * 3) * 3 )", "ParenthesMiddleMultiply", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("54", output);
}

TEST(Parser, ParenthesMiddleMixedValid)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 + (3 * 3) + 3 )", "ParenthesMiddleMixedValid", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("14", output);
}

TEST(Parser, ParenthesMiddleMixedValidTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 * (3 + 3) * 3 )", "ParenthesMiddleMixedValidTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("36", output);
}

TEST(Parser, ParenthesMiddleMixedInvalid)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 * (3 + 3) + 3 )", "ParenthesMiddleMixedInvalid", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ParenthesMiddleMixedInvalidTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 + (3 * 3) * 3 )", "ParenthesMiddleMixedInvalidTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, JustAPlus)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("+", "JustAPlus", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidOperator)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("-", "InvalidOperator", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidOperatorTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(10-3)", "InvalidOperatorTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, JustARShift)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(">", "JustARShift", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, JustALShift)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("<", "JustALShift", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, JustAPlusParen)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(+)", "JustAPlusParen", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, JustAMinusParen)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(-)", "JustAMinusParen", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, JustARShiftParen)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(>)", "JustARShiftParen", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, NotParentheses)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("[2+6]", "NotParentheses", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, NotParenthesesTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("{2+6}", "NotParenthesesTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ZeroBeforeInteger)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(02+6)", "ZeroBeforeInteger", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("8", output);
}

TEST(Parser, ZeroBeforeIntegerTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(02+00006)", "ZeroBeforeInteger", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("8", output);
}

TEST(Parser, JustALShiftParen)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(<)", "JustALShiftParen", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
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

// Test for edge case (eg.: "(2 + 1 1)").
// Disabled because of Piazza comment noting we do not have to check for this
TEST(DISABLED_Parser, SpaceInNumber)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 11 + 2 + 1 1)", "SpaceInNumber", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}
