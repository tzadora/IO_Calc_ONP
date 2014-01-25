#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
	TEST_CLASS(TestClassRPN)
	{
	public:
		TEST_METHOD(calcNumber)
		{
			string expression = "154";
			double result = 154.0;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcNumberWithMinus)
		{
			string expression = "-154";
			double result = -154.0;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcNumberWithDot)
		{
			string expression = "154.11";
			double result = 154.11;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcNumberWithDotAndMinus)
		{
			string expression = "-11.1222";
			double result = -11.1222;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionAdd)
		{
			string expression = "-11.1222 + 1.0";
			double result = -10.1222;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionSub)
		{
			string expression = "-11.1222 - 1.0";
			double result = -12.1222;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionMul)
		{
			string expression = "-11.1222*1.0";
			double result = -11.1222;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionDiv)
		{
			string expression = "-11.1222 /1.0";
			double result = -11.1222;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionPow)
		{
			string expression = "-11.1222 ^ 1.0";
			double result = -11.1222;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionCos)
		{
			string expression = "cos(60)";
			double result = 0.5;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionBrackets)
		{
			string expression = "(1)";
			double result = 1.0;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionSin)
		{
			string expression = "sin(30)";
			double result = 0.5;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpressionSqrt)
		{
			string expression = "sqrt(16)";
			double result = 4.0;
			Test::testCalculateMethod(expression, result);
		}

		TEST_METHOD(calcExpression)
		{
			string expression = "sqrt(4) + 2 * 2";
			double result = 6;
			Test::testCalculateMethod(expression, result);
		}
	};
}
