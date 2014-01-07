#include <iostream>
#include <string.h>
#include <cmath>
#include <cctype>
#include <list>
#include <stack>
#include "Parser.h"
#include "rpn.h"


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

	////test parsera czy dziala
	//for (list<Symbol>::iterator iter = listOfSymbols.begin(); iter != listOfSymbols.end(); iter++)
	//{
	//	cout << iter->showSymbol().c_str() << endl;
	//}
	//cout << "END PARSER TEST" << endl << endl;
	//
	if (!toPostfixNotation())
		return 0.0;

	////test postfix
	//for (list<Symbol>::iterator iter = listOfSymbols.begin(); iter != listOfSymbols.end(); iter++)
	//{
	//	cout << iter->showSymbol().c_str() << endl;
	//}

	//cout << "END POSTFIX TEST" << endl << endl;

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
	getValueFromStack(&a);
	stackOfValues.push((currentSymbol.getFun())(a));
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
