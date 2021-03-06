#include <iostream>
#include <string.h>
#include <cmath>
#include <cerrno>
#include <cfenv>
#pragma STDC FENV_ACCESS on
#include <cctype>
#include <list>
#include <stack>
#include "Parser.h"
#include "rpn.h"


#define PI 3.14159265


using namespace std;

ReversePolishNotation::ReversePolishNotation()
{
	listOfSymbols.clear();
}

/*******************************************************************/
//metoda obliczajaca wynik i idaca przez wszystkie kroki wykonywania 

double ReversePolishNotation::calculate(const std::string & expression)
{
	//przygotowanie do parsowania 
	this->expression = expression;
	Parser parser(expression, listOfSymbols);
	if (!parser.parse())
		return 0.0;

	if (!toPostfixNotation())
		return 0.0;

	return toResult();
}

/*******************************************************************/
//metoda przeksztalcajaca liste symboli do postaci postfixowej

bool ReversePolishNotation::toPostfixNotation()
{
	//robimy kopie listy symboli 
	list<Symbol> tempSymbols(listOfSymbols);
	
	//wyczyszczamy liste z klasy
	listOfSymbols.clear();

	//ustawienie flagi bledow 
	errors = false;

	for (list<Symbol>::iterator iter = tempSymbols.begin(); iter != tempSymbols.end(); iter++)
	{
		currentSymbol = *iter;
		switch (iter->getType())
		{
		case NUMBER:
			actionNumber();
			break;

		case OPERATOR:
			actionOperator();
			break;

		case BRACKET_BEGIN:
			actionBracketBegin();
			break;

		case BRACKET_END:
			actionBracketEnd();
			break;

		case FUNCTION:
			actionFunction();
			break;

		default:
			errors = true;
			errorMessage = "Blad - Wystapil nieoczekiwny symbol podczas przetwarzania";
		}

		if (errors)
		{
			cerr << errorMessage.c_str() << endl;
			return false;
		}
	}

	//oproznij stos na wyjscie
	while (!stackOfSymbols.empty())
	{
		listOfSymbols.push_back(stackOfSymbols.top());
		stackOfSymbols.pop();
	}

	return true;
}

/*******************************************************************/
//Metody dla poszczegolnych akcji 
//podczas przeksztalcania z notacji infixowej do postfixowej

//Akcja dla liczb

void ReversePolishNotation::actionNumber()
{
	//obiekt idzie na wyjscie 
	listOfSymbols.push_back(currentSymbol);
}

/*******************************************************************/
//Akcja dla operatora

void ReversePolishNotation::actionOperator()
{
	while (!stackOfSymbols.empty())
	{	
		//jesli priorytet op wej >= op na stosie to zloz op ze stosu do wyjscia
		if (currentSymbol.getPriority() <= stackOfSymbols.top().getPriority())
		{
			listOfSymbols.push_back(stackOfSymbols.top());
			stackOfSymbols.pop();
		}
		else
			break;
	}
	
	//dodaj na stos op wej
	stackOfSymbols.push(currentSymbol);
}


/*******************************************************************/
//Akcja dla nawiasu (

void ReversePolishNotation::actionBracketBegin()
{
	stackOfSymbols.push(currentSymbol);
}

/*******************************************************************/
//Akcja dla nawiasu )

void ReversePolishNotation::actionBracketEnd()
{
	//czy znaleziono nawias (
	bool foundBeginBracket = false;

	while (!stackOfSymbols.empty())
	{
		if (stackOfSymbols.top().getType() != BRACKET_BEGIN)
		{
			listOfSymbols.push_back(stackOfSymbols.top());
			stackOfSymbols.pop();
		}

		//jesli znaleziono nawias (
		else
		{
			stackOfSymbols.pop();
			foundBeginBracket = true;
			break;
		}
	}

	if (!foundBeginBracket)
	{
		errors = true;
		errorMessage = "Blad - Brakujacy nawias (";
	}
}

/*******************************************************************/
//Akcja dla funkcji

void ReversePolishNotation::actionFunction()
{
	actionOperator();
}

/*******************************************************************/
//METODA OBLICZAJACA WYNIK KONCOWY
/*******************************************************************/

double ReversePolishNotation::toResult()
{
	for (list<Symbol>::iterator iter = listOfSymbols.begin(); iter != listOfSymbols.end(); iter++)
	{
		currentSymbol = *iter;
		switch (iter->getType())
		{
		case NUMBER:
			resultNumber();
			break;

		case OPERATOR:
			resultOperator();
			break;

		case FUNCTION:
			resultFunction();
			break;

		default:
			errors = true;
			errorMessage = "Blad - Napotkano nieoczekiwany symbol";
			break;
		}

		if (errors)
		{
			cerr << errorMessage.c_str() << endl;
			return 0.0;
		}
	}

	return stackOfValues.top();
}

/*******************************************************************/
//Metoda obslugujaca wystapienie liczby

void ReversePolishNotation::resultNumber()
{
	stackOfValues.push(atof(currentSymbol.showSymbol().c_str()));
}

/*******************************************************************/
//Metoda obslugujaca wystapienie operatora

void ReversePolishNotation::resultOperator()
{
	double a, b;
	getValueFromStack(&a);
	getValueFromStack(&b);

	stackOfValues.push((currentSymbol.*currentSymbol.getFun2())(b, a));
}

/*******************************************************************/
//Metoda obslugujaca wystapienie funkcji

void ReversePolishNotation::resultFunction()
{
	double a;

	//czyscimy wyjatki jesli by jakies byly
	errno = 0;
	if (math_errhandling & MATH_ERREXCEPT) feclearexcept(FE_ALL_EXCEPT);

	getValueFromStack(&a);

	//zmiena na stopnie jesli jest to funkcja trygonometryczna 
	if (currentSymbol.showSymbol() == "cos" || currentSymbol.showSymbol() == "sin")
		a = a * PI / 180;

	stackOfValues.push((currentSymbol.getFun())(a));

	sqrtErrorCheck();
}

/*******************************************************************/
//Metoda pobiera wartosc ze stosu a gdy sie nie uda informuje o bledzie

void ReversePolishNotation::getValueFromStack(double* a)
{
	if (!stackOfValues.empty())
	{
		*a = stackOfValues.top();
		stackOfValues.pop();
	}
	else
	{
		errors = true;
		errorMessage = "Blad - Nie mozna pobrac liczb";
	}
}

/*******************************************************************/
//Metoda sprawdzajaca czy wystapil blad podczas pierwiastkowania

void ReversePolishNotation::sqrtErrorCheck()
{
	//obsluga gdy sqrt(-1)
	if (math_errhandling & MATH_ERRNO)
	{
		if (errno == EDOM)
			sqrtNegativeError();
	}
	else if (math_errhandling & MATH_ERREXCEPT)
	{
		if (fetestexcept(FE_INVALID))
			sqrtNegativeError();
	}
}

/*******************************************************************/
//Metoda reagujaca na blad podczas pierwiastkowania

void ReversePolishNotation::sqrtNegativeError()
{
	cerr << "Blad - Pierwiastek z liczby ujemnej" << endl;
	//wstawiamy na stos 0 jako wynik niewlasciwyhc dzialan
	stackOfValues.pop();
	stackOfValues.push(0.0);
}
