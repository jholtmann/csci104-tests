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
  EXPECT_TRUE(runParserProgram("(<2 + <9)", "ShiftComplex", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("22", output);
}

TEST(Parser, ShiftToZero)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(">>>6", "ShiftToZero", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("0", output);
}

TEST(Parser, ShiftToZeroTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(">>>>>>>>>>>>>>>>>>>>6", "ShiftToZeroTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("0", output);
}

TEST(Parser, ShiftToOne)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(">>>>>><<<<<<1", "ShiftToOne", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("1", output);
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

TEST(Parser, ShiftOutsideParentheses)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("<<(<2 + 7)", "ShiftOutsideParentheses", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("44", output);
}

TEST(Parser, ShiftOutsideParenthesesMixedAddition)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("<1+1<(<2 + 7)", "ShiftOutsideParenthesesMixedAddition", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ShiftOutsideParenthesesMixedNumber)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("<11<(<2 + 7)", "ShiftOutsideParenthesesMixedNumber", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, BlankLine)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("", "BlankLine", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("", output);
}

TEST(Parser, BlankLineTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(" ", "BlankLineTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("", output);
}

TEST(Parser, BlankLineThree)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("\t", "BlankLineThree", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("", output);
}

TEST(Parser, AdjacentOperators)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 +* 8)", "AdjacentOperators", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, AdjacentOperatorsTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 ** 8)", "AdjacentOperatorsTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, AdjacentOperatorsThree)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 * * 8)", "AdjacentOperatorsThree", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, AdjacentOperatorsFour)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 <*  8)", "AdjacentOperatorsThree", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, AdjacentOperatorsValid)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 * <8)", "AdjacentOperatorsValid", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("32", output);
}

TEST(Parser, AdjacentOperatorsValidTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 *<8)", "AdjacentOperatorsValidTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("32", output);
}

TEST(Parser, MissingOperatorParenthesis)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 + (8*3)5)", "MissingOperatorParenthesis", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MissingOperatorParenthesisTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 + 5(8*3))", "MissingOperatorParenthesisTwo", output));
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

TEST(Parser, InvalidCharJustLetters)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("abc", "InvalidCharJustLetters", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidCharLettersAtEnd)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(5 + 5)feelsbadman", "InvalidCharLettersAtEnd", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidCharScatteredLetters)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("a(40 b + 5 c)", "InvalidCharScatteredLetters", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidCharLettersOnlyInside)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(5 x + y 5)", "InvalidCharLettersOnlyInside", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidCharHappyFace)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(":)", "InvalidCharHappyFace", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidCharSadFace)
{
  std::string output;
  EXPECT_TRUE(runParserProgram(":(", "InvalidCharSadFace", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidCharNeutralFace)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(0 _ 0)", "InvalidCharNeutralFace", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
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

TEST(Parser, TooManyParentheses)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("((<123*234))", "TooManyParentheses", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, TooManyParenthesesShifted)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(<>(<123*234))", "TooManyParenthesesShifted", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, TooManyParenthesesTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("((<123*234*2))", "TooManyParenthesesTwo", output));
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
  EXPECT_TRUE(runParserProgram("(1138*3720*)", "ExtraTimesTwo", output));
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

TEST(Parser, MixingOperatorsShifted)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1+2*>3)", "MixingOperatorsShifted", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MixingOperatorsMidway)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1+1+2*3+5+6+7)", "MixingOperatorsMidway", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MixingOperatorsEarly)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1+1+2+3+5+6*7)", "MixingOperatorsEarly", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, MixingOperatorsAtEnd)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1*1+2+3+5+6+7)", "MixingOperatorsAtEnd", output));
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

TEST(Parser, MultipleTimesOperatorsTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2*2 *2*2*2 *2* 2 * 2)", "MultipleTimesOperatorsTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("256", output);
}

TEST(Parser, MultipleOperators)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(<<14 *(>>123+333 ))", "MultipleOperators", output));
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

TEST(Parser, ParenthesesMiddleAdd)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 + (3 + 3) + 3 )", "ParenthesesMiddleAdd", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("11", output);
}

TEST(Parser, ParenthesesMiddleMultiply)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 * (3 * 3) * 3 )", "ParenthesesMiddleMultiply", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("54", output);
}

TEST(Parser, ParenthesesMiddleDouble)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("((100*200)+(100+200))", "ParenthesesMiddleDouble", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("20300", output);
}

TEST(Parser, ParenthesesMiddleMixedValid)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 + (3 * 3) + 3 )", "ParenthesesMiddleMixedValid", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("14", output);
}

TEST(Parser, ParenthesesMiddleMixedValidTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 * (3 + 3) * 3 )", "ParenthesesMiddleMixedValidTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("36", output);
}

TEST(Parser, ParenthesesMiddleMixedInvalid)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 * (3 + 3) + 3 )", "ParenthesesMiddleMixedInvalid", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ParenthesesMiddleMixedInvalidTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( 2 + (3 * 3) * 3 )", "ParenthesesMiddleMixedInvalidTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, ParentesesMiddleLots)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( ((7+2) + (3*3) + (9*12578)) * 3)", "ParentesesMiddleLots", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("339660", output);
}

TEST(Parser, ParentesesMiddleShift)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("( ((<7+2) + (<3*3) + (9*12578)) * 3)", "ParentesesMiddleShift", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("339708", output);
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

TEST(Parser, JustAPlus)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("+", "JustAPlus", output));
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

TEST(Parser, JustATimesParen)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(*)", "JustATimesParen", output));
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

TEST(Parser, JustALShiftParen)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(<)", "JustALShiftParen", output));
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

TEST(Parser, ZeroBeforeIntegerThree)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(02+0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000006)", "ZeroBeforeIntegerThree", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("8", output);
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

// All expressions listed on assignment page
TEST(Parser, MultipleExpressionsTwo)
{
  std::string output;
std::string expression =    "((<123*234)\n"
                            "(1337*9001+42)\n"
                            "(*1138*3720)\n"
                            "(<<14 *(>>123+333 ))\n"
                            "<>(2 * 1* ( >500000000 + <<0))\n"
                            "<>(1 * >3 * 3)\n";

  std::string expected =    "Malformed"
                            "Malformed"
                            "Malformed"
                            "20328"
                            "500000000"
                            "2";

  EXPECT_TRUE(runParserProgram(expression, "MultipleExpressionsTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ(expected, output);
}

TEST(Parser, LotsOfWhitespace)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("    (1            + 2            )            ", "LotsOfWhitespace", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("3", output);
}

TEST(Parser, LotsOfTabs)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("\t(1\t\t\t\t\t\t+ 2\t\t\t  \t   \t   \t  )  \t   \t  \t \t   \t", "LotsOfWhitespace", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("3", output);
}


TEST(Parser, AddZero)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(550 + 0)", "AddZero", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("550", output);
}

TEST(Parser, MultiplyZero)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(550 * 0)", "MultiplyZero", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("0", output);
}

TEST(Parser, MultiplyZeroTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(550 * 0 * 1 * 252314234 * 1)", "MultiplyZeroTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("0", output);
}

TEST(Parser, DoubleInput)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(550.0 + 0)", "DoubleInput", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidOperatorSubtraction)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(100 - 200)", "InvalidOperatorSubtraction", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, InvalidOperatorDivision)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(100 / 200)", "InvalidOperatorDivision", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, AdjacentExpressions)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(100 + 200)(100 + 200)", "AdjacentExpressions", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, AdjacentExpressionsTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(100 + 200)+(100 + 200)", "AdjacentExpressionsTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("Malformed", output);
}

TEST(Parser, Complex)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(1 * 1 * 2 * (><2+<<1) * (3+2) * (5 + <3))", "Complex", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("660", output);
}

TEST(Parser, ComplexTwo)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("(2 + ( 2 * ( (9 * (3*3))+<4)*<6) + 4)", "ComplexTwo", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("2142", output);
}

TEST(Parser, ReallyLongInput)
{
  std::string output;
  std::string input = "(1 ";
  for (int i = 0; i < 10000; i++) {
    input += "+ 1";
  }
  input += ")";

  EXPECT_TRUE(runParserProgram(input, "ReallyLongInput", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("10001", output);
}

TEST(Parser, HalfIntMaxMultiply)
{
  std::string output;
  std::string input = "(2 ";
  for (int i = 0; i < 29; i++) {
    input += "* 2";
  }
  input += ")";

  EXPECT_TRUE(runParserProgram(input, "HalfIntMaxMultiply", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("1073741824", output);
}

TEST(Parser, HalfIntMaxLeftShift)
{
  std::string output;
  EXPECT_TRUE(runParserProgram("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<2", "HalfIntMaxLeftShift", output));
  output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
  EXPECT_EQ("1073741824", output);
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
