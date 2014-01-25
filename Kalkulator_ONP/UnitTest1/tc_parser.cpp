#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
	TEST_CLASS(TestClassParser)
	{
	public:
		TEST_METHOD(parseNumberType)
		{
			string expression = "12";
			Test::testSingleExpressionType(expression, NUMBER);
		}

		TEST_METHOD(parseNumber)
		{
			string expression = "154";
			Test::testSingleExpression(expression);
		}

		TEST_METHOD(parseNumberWithMinusType)
		{
			string expression = "-154";
			Test::testSingleExpressionType(expression, NUMBER);
		}

		TEST_METHOD(parseNumberWithMinus)
		{
			string expression = "-154";
			Test::testSingleExpression(expression);
		}

		TEST_METHOD(parseNumberWithDotType)
		{
			string expression = "11.1222";
			Test::testSingleExpressionType(expression, NUMBER);
		}

		TEST_METHOD(parseNumberWithDot)
		{
			string expression = "11.1222";
			Test::testSingleExpression(expression);
		}

		TEST_METHOD(parseNumberWithDotAndMinusType)
		{
			string expression = "-11.1222";
			Test::testSingleExpressionType(expression, NUMBER);
		}

		TEST_METHOD(parseNumberWithDotAndMinus)
		{
			string expression = "-11.1222";
			Test::testSingleExpression(expression);
		}

		TEST_METHOD(parseExpressionAdd)
		{
			string expression = "-11.1222 + 1.0";
			list<tokenType> listOfTokens = { NUMBER, OPERATOR, NUMBER };
			Test::testExpression(expression, listOfTokens);
		}

		TEST_METHOD(parseExpressionSub)
		{
			string expression = "-11.1222 - 1.0";
			list<tokenType> listOfTokens = { NUMBER, OPERATOR, NUMBER };
			Test::testExpression(expression, listOfTokens);
		}

		TEST_METHOD(parseExpressionMul)
		{
			string expression = "-11.1222* 1.0";
			list<tokenType> listOfTokens = { NUMBER, OPERATOR, NUMBER };
			Test::testExpression(expression, listOfTokens);
		}

		TEST_METHOD(parseExpressionDiv)
		{
			string expression = "-11.1222 /1.0";
			list<tokenType> listOfTokens = { NUMBER, OPERATOR, NUMBER };
			Test::testExpression(expression, listOfTokens);
		}

		TEST_METHOD(parseExpressionPow)
		{
			string expression = "-11.1222 ^ 1.0";
			list<tokenType> listOfTokens = { NUMBER, OPERATOR, NUMBER };
			Test::testExpression(expression, listOfTokens);
		}

		TEST_METHOD(parseExpressionCos)
		{
			string expression = "cos(2)";
			list<tokenType> listOfTokens = { FUNCTION, BRACKET_BEGIN, NUMBER, BRACKET_END };
			Test::testExpression(expression, listOfTokens);
		}

		TEST_METHOD(parseExpressionBrackets)
		{
			string expression = "(1)";
			list<tokenType> listOfTokens = {BRACKET_BEGIN, NUMBER, BRACKET_END };
			Test::testExpression(expression, listOfTokens);
		}


		TEST_METHOD(parseExpressionSin)
		{
			string expression = "sin(2)";
			list<tokenType> listOfTokens = { FUNCTION, BRACKET_BEGIN, NUMBER, BRACKET_END };
			Test::testExpression(expression, listOfTokens);
		}

		TEST_METHOD(parseExpressionSqrt)
		{
			string expression = "sqrt(2)";
			list<tokenType> listOfTokens = { FUNCTION, BRACKET_BEGIN, NUMBER, BRACKET_END };
			Test::testExpression(expression, listOfTokens);
		}

		TEST_METHOD(parseExpressionBracketOpN)
		{
			string expression = "sqrt(2) * 1";
			list<tokenType> listOfTokens = { FUNCTION, BRACKET_BEGIN, NUMBER, BRACKET_END, OPERATOR, NUMBER };
			Test::testExpression(expression, listOfTokens);
		}
	};
}
