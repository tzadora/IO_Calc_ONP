#include <iostream>
#include <cmath>
#include "Symbol.h"

using namespace std;

//konstruktor domyslny
Symbol::Symbol()
{
	;
}


//Konstruktor - uzupelnia pola klasy Symbol
Symbol::Symbol(string content, tokenType tt)
{
	this->content = content;
	this->type = tt;
	priority = 0;
	fun = NULL;
	fun2 = NULL;

	setIfOperator();
	setIfFunction();
}

/*******************************************************************/
//Metoda ustawiajaca parametry operatora

void Symbol::setIfOperator()
{
	if (type == OPERATOR)
	{
		if (content == "-")
		{
			priority = 1;
			fun2 = &Symbol::subtraction;
		}
		else if (content == "+")
		{
			priority = 1;
			fun2 = &Symbol::addition;
		}
		else if (content == "*")
		{
			priority = 2;
			fun2 = &Symbol::multiplication;
		}
		else if (content == "/")
		{
			priority = 2;
			fun2 = &Symbol::division;
		}
		else if (content == "^")
		{
			priority = 3;
			fun2 = &Symbol::exponentiation;
		}
	}
}

/*******************************************************************/
//Metoda ustawiajaca parametry funkcji

void Symbol::setIfFunction()
{
	//ustawienie wskaznika na fun na podstawie content 
	if (type == FUNCTION)
	{
		if (content == "sqrt")
			fun = sqrt;

		else if (content == "sin")
			fun = sin;

		else if (content == "cos")
			fun = cos;

		else
			fun = NULL;

		priority = 4;
	}
	else
		fun = NULL;
}


/*******************************************************************/
//Metoda pokazujaca symbol

string Symbol::showSymbol()
{
	return content;
}

/*******************************************************************/
//Metoda zwracajaca wskaznik do funkcji

double(*Symbol::getFun())(double)
{
	return fun;
}

/*******************************************************************/
//Metoda zwracajaca wskaznik do funkcji

double(Symbol::*Symbol::getFun2())(double, double)
{
	return fun2;
}

/*******************************************************************/
//Metoda zwracajaca typ

tokenType Symbol::getType()
{
	return type;
}

/*******************************************************************/
//Metoda zwracajaca priorytet

int Symbol::getPriority()
{
	return priority;
}


/*******************************************************************/
//FUNKCJE DO OPERATOROW
/*******************************************************************/

double Symbol::addition(double a, double b)
{
	return a + b;
}

/*******************************************************************/

double Symbol::subtraction(double a, double b)
{
	return a - b;
}

/*******************************************************************/

double Symbol::multiplication(double a, double b)
{
	return a * b;
}

/*******************************************************************/

double Symbol::division(double a, double b)
{
	if (b == 0.0)
	{
		//nie mozna dzielic przez zero!
		cerr << "Blad - Nie mozna dzielic przez zero!" << endl;
		return 0.0;
	}
	return a / b;
}

/*******************************************************************/

double Symbol::exponentiation(double a, double b)
{
	return pow(a, b);
}

/*******************************************************************/
