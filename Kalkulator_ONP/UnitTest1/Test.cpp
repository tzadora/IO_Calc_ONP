#include "stdafx.h"
#include "Test.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

list<Symbol> Test::listOfSymbols;
//****************************************************************
//metoda statyczna symulujaca proces parsowania

void Test::parse(std::string expression)
{
	Test::listOfSymbols.clear();

	Parser* parser = new Parser(expression, Test::listOfSymbols);
	if (!parser->parse())
	{
		delete parser;
		Assert::Fail();
	}
	delete parser;
}

//****************************************************************
//metoda statyczna sprawdzajaca czy zwracana wartosc jest poprawna 

void Test::testSingleExpression(string expression)
{
	Test::parse(expression);
	Assert::AreEqual(expression, Test::listOfSymbols.begin()->showSymbol());
}

//****************************************************************
//metoda statyczna sprawdzajaca czy podana wartosc jest klasyfikowana do 
//wlasciwego typu 

void Test::testSingleExpressionType(string expression, tokenType type)
{
	Test::parse(expression);
	Assert::AreEqual((int)type, (int)(Test::listOfSymbols.begin()->getType()));
}

//****************************************************************
//metoda statyczna sprawdzajaca poparwnosc parsowania wyrazenia 3 symboli 
//np. 1+1

void Test::testExpression(std::string expression, list<tokenType> listOfTokens)
{
	Test::parse(expression);
	list<Symbol>::iterator iters = Test::listOfSymbols.begin();
	for (list<tokenType>::iterator iter = listOfTokens.begin(); iter != listOfTokens.end(); iter++)
	{
		Assert::AreEqual((int)*iter, (int)(iters->getType()));
		iters++;
	}
}

//****************************************************************
//metody statyczne sprawdzajace czy podany string jest tym czego chcemy

void Test::testExpectedSymbolIsFalse(std::string expression, tokenType type)
{
	ExpectedSymbol* symbol = new ExpectedSymbol;
	Assert::IsFalse(symbol->check(expression, type));
	delete symbol;
}

//
void Test::testExpectedSymbolIsTrue(std::string expression, tokenType type)
{
	ExpectedSymbol* symbol = new ExpectedSymbol;
	Assert::IsTrue(symbol->check(expression, type));
	delete symbol;
}

//****************************************************************
//metody statyczne sprawdzajace czy operator dobrze wykonuje swoje dzialanie 

void Test::testOperation(Symbol* s1, Symbol* s2, Symbol* op, double result)
{
	double a = atof(s1->showSymbol().c_str());
	double b = atof(s2->showSymbol().c_str());
	Assert::AreEqual(result, (op->*op->getFun2())(a, b));
	delete s1;
	delete s2;
	delete op;
}

//****************************************************************
//metoda statyczna sprawdzajaca czy funkcja wykonuje swoje zadanie 

void Test::testFunction(Symbol* s1, Symbol* fun, double result)
{
	double a = atof(s1->showSymbol().c_str());
	Assert::AreEqual(result, (fun->getFun())(a), 0.01);
	delete s1;
	delete fun;
}

//****************************************************************
//metoda statyczna sprawdzajaca czy kalkulator podaje dobre wyniki obliczen

void Test::testCalculateMethod(std::string expression, double result)
{
	ReversePolishNotation* rpn = new ReversePolishNotation;
	Assert::AreEqual(result, rpn->calculate(expression), 0.01);
}
