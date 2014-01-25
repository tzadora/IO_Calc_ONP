#include "stdafx.h"
#include "CppUnitTest.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{
	TEST_CLASS(TestClassSymbol)
	{
	public:
		TEST_METHOD(testShowSymbol)
		{
			Symbol* symbol = new Symbol("12", NUMBER);
			Assert::AreEqual(string("12"), symbol->showSymbol());
			delete symbol;
		}

		TEST_METHOD(testAddition)
		{
			Symbol* s1 = new Symbol("12", NUMBER);
			Symbol* s2 = new Symbol("12", NUMBER);
			Symbol* op = new Symbol("+", OPERATOR);
			double result = 24.0;
			Test::testOperation(s1, s2, op, result);
		}

		TEST_METHOD(testSubtraction)
		{
			Symbol* s1 = new Symbol("12", NUMBER);
			Symbol* s2 = new Symbol("12", NUMBER);
			Symbol* op = new Symbol("-", OPERATOR);
			double result = 0.0;
			Test::testOperation(s1, s2, op, result);
		}

		TEST_METHOD(testMultiplication)
		{
			Symbol* s1 = new Symbol("12", NUMBER);
			Symbol* s2 = new Symbol("12", NUMBER);
			Symbol* op = new Symbol("*", OPERATOR);
			double result = 144.0;
			Test::testOperation(s1, s2, op, result);
		}

		TEST_METHOD(testDivision)
		{
			Symbol* s1 = new Symbol("12", NUMBER);
			Symbol* s2 = new Symbol("12", NUMBER);
			Symbol* op = new Symbol("/", OPERATOR);
			double result = 1.0;
			Test::testOperation(s1, s2, op, result);
		}

		TEST_METHOD(testPower)
		{
			Symbol* s1 = new Symbol("0.5", NUMBER);
			Symbol* s2 = new Symbol("-1", NUMBER);
			Symbol* op = new Symbol("^", OPERATOR);
			double result = 2.0;
			Test::testOperation(s1, s2, op, result);
		}

		TEST_METHOD(testSin)
		{
			Symbol* s1 = new Symbol("0", NUMBER);
			Symbol* fun = new Symbol("sin", FUNCTION);
			double result = 0.0;
			Test::testFunction(s1, fun, result);
		}

		TEST_METHOD(testCos)
		{
			Symbol* s1 = new Symbol("0", NUMBER);
			Symbol* fun = new Symbol("cos", FUNCTION);
			double result = 1.0;
			Test::testFunction(s1, fun, result);
		}

		TEST_METHOD(testSqrt)
		{
			Symbol* s1 = new Symbol("4", NUMBER);
			Symbol* fun = new Symbol("sqrt", FUNCTION);
			double result = 2.0;
			Test::testFunction(s1, fun, result);
		}

		TEST_METHOD(testPriority)
		{
			Symbol* sqrt = new Symbol("sqrt", FUNCTION);
			Assert::AreEqual(4, (sqrt->getPriority()));
			delete sqrt;
		}

		TEST_METHOD(testType)
		{
			Symbol* sqrt = new Symbol("sqrt", FUNCTION);
			Assert::AreEqual((int)FUNCTION, (int)(sqrt->getType()));
			delete sqrt;
		}
	};
}
