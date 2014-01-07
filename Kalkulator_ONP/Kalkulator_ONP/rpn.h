#pragma once

#include <list>
#include <stack>
#include "Symbol.h"

class ReversePolishNotation
{
private:
	std::string expression;
	std::list<Symbol> listOfSymbols;
	std::stack<Symbol> stackOfSymbols;
	std::stack<double> stackOfValues;
	Symbol currentSymbol;
	bool errors = false;
	std::string errorMessage = "";
	
	//metody odpowiedzialne za przeksztalcenia
	bool toPostfixNotation();
	double toResult(); 

	//metody pomocnicze
	void actionNumber();
	void actionOperator();
	void actionBracketBegin();
	void actionBracketEnd();
	void actionFunction();

	void resultNumber();
	void resultOperator();
	void resultFunction();

	void getValueFromStack(double* a);

	
public:

	ReversePolishNotation();								//konstruktor 
	double calculate(const std::string & expression);		//funkcja obliczajaca - sterujaca 
			
};
