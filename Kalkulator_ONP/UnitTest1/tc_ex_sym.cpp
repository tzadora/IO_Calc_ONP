#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{		
	TEST_CLASS(TestClassExpectedSymbol)
	{
	public:
		//metoda check	T = true	F = false
		TEST_METHOD(checkForNumberT)
		{
			string expression = "2";
			tokenType type = NUMBER;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForNumberF)
		{
			string expression = "c";
			tokenType type = NUMBER;
			Test::testExpectedSymbolIsFalse(expression, type);
			expression = "{";
			Test::testExpectedSymbolIsFalse(expression, type);
			expression = "*";
			Test::testExpectedSymbolIsFalse(expression, type);
		}

		TEST_METHOD(checkForBracketBeginT)
		{
			string expression = "(";
			tokenType type = BRACKET_BEGIN;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForBracketBeginF)
		{
			string expression = ")";
			tokenType type = BRACKET_BEGIN;
			Test::testExpectedSymbolIsFalse(expression, type);
		}

		TEST_METHOD(checkForBracketEndT)
		{
			string expression = ")";
			tokenType type = BRACKET_END;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForBracketEndF)
		{
			string expression = "*";
			tokenType type = BRACKET_END;
			Test::testExpectedSymbolIsFalse(expression, type);
		}

		TEST_METHOD(checkForDotT)
		{
			string expression = ".";
			tokenType type = DOT;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForDotF)
		{
			string expression = "l";
			tokenType type = DOT;
			Test::testExpectedSymbolIsFalse(expression, type);
		}

		TEST_METHOD(checkForFunctionSin)
		{
			string expression = "sin";
			tokenType type = FUNCTION;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForFunctionCos)
		{
			string expression = "cos";
			tokenType type = FUNCTION;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForFunctionSqrt)
		{
			string expression = "sqrt";
			tokenType type = FUNCTION;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForFunctionF)
		{
			string expression = "abc";
			tokenType type = FUNCTION;
			Test::testExpectedSymbolIsFalse(expression, type);
		}

		TEST_METHOD(checkForLetterT)
		{
			string expression = "a";
			tokenType type = LETTER;
			Test::testExpectedSymbolIsTrue(expression, type);
			expression = "z";
			Test::testExpectedSymbolIsTrue(expression, type);
			expression = "A";
			Test::testExpectedSymbolIsTrue(expression, type);
			expression = "Z";
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForLetterF)
		{
			string expression = "1";
			tokenType type = LETTER;
			Test::testExpectedSymbolIsFalse(expression, type);
			expression = "(";
			Test::testExpectedSymbolIsFalse(expression, type);
			expression = "/";
			Test::testExpectedSymbolIsFalse(expression, type);
		}

		TEST_METHOD(checkForOperatorP)
		{
			string expression = "+";
			tokenType type = OPERATOR;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForOperatorM)
		{
			string expression = "-";
			tokenType type = OPERATOR;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForOperatorMu)
		{
			string expression = "*";
			tokenType type = OPERATOR;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForOperatorD)
		{
			string expression = "/";
			tokenType type = OPERATOR;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForOperatorPow)
		{
			string expression = "^";
			tokenType type = OPERATOR;
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForOperatorF)
		{
			ExpectedSymbol* symbol = new ExpectedSymbol;
			string op = "z";
			Assert::IsFalse(symbol->check(op, OPERATOR));
			delete symbol;
		}

		TEST_METHOD(checkForPlusMinusT)
		{
			string expression = "+";
			tokenType type = OPERATOR;
			Test::testExpectedSymbolIsTrue(expression, type);
			expression = "-";
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForPlusMinusF)
		{
			string expression = "1";
			tokenType type = PLUSMINUS;
			Test::testExpectedSymbolIsFalse(expression, type);
		}

		TEST_METHOD(checkForWhiteSpaceT)
		{
			string expression = " ";
			tokenType type = WHITE_SPACE;
			Test::testExpectedSymbolIsTrue(expression, type);
			expression = "\t";
			Test::testExpectedSymbolIsTrue(expression, type);
		}

		TEST_METHOD(checkForWhiteSpaceF)
		{
			string expression = "x";
			tokenType type = WHITE_SPACE;
			Test::testExpectedSymbolIsFalse(expression, type);
		}
	};
}
