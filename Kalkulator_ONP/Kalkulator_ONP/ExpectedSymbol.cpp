#include <iostream>
#include <cctype>
#include <list>
#include <unordered_map>
#include "ExpectedSymbol.h"
using namespace std;

/********************************************************************/
//Metoda sprawdzajaca czy dany znak jest cyfra
bool ExpectedSymbol::isNumber(const string & c)
{
	return (isdigit(c[0]));
}

/********************************************************************/
//Metoda sprawdzajaca czy dany znak jest operatorem

bool ExpectedSymbol::isOperator(const string & c)
{
	list<char> listOfOperators;
	listOfOperators.push_back('+');
	listOfOperators.push_back('-');
	listOfOperators.push_back('*');
	listOfOperators.push_back('/');
	listOfOperators.push_back('^');

	for (list<char>::iterator iter = listOfOperators.begin(); iter != listOfOperators.end(); iter++)
	{
		if (c[0] == *iter)
		{
			return true;
		}
	}
	return false;
}

/****************************************************************************/
// Metoda sprawdza czy podany string ma szanse byc nazwa funkcji

bool ExpectedSymbol::isFunction(const string & fun)
{
	list<string> namesOfFunctions;
	namesOfFunctions.push_back("sqrt");
	namesOfFunctions.push_back("sin");
	namesOfFunctions.push_back("cos");

	for (list<string>::iterator iter = namesOfFunctions.begin(); iter != namesOfFunctions.end(); iter++)
	{
		if (*iter == fun)
		{
			return true;
		}
	}
	return false;
}

/****************************************************************************/
// Metoda sprawdza czy podany znak jest kropka

bool ExpectedSymbol::isDot(const string & dot)
{
	return (dot[0] == '.');
}

/****************************************************************************/
// Metoda sprawdza czy podany znak jest kropka

bool ExpectedSymbol::isPlusMinus(const string & pm)
{
	return (pm[0] == '+' || pm[0] == '-');
}


/****************************************************************************/
// Metoda sprawdza czy podany znak jest bialym znakiem

bool ExpectedSymbol::isWhiteSpace(const string & c)
{
	return (c[0] == ' ' || c[0] == '\t' || c[0] == '\n');
}

/****************************************************************************/
// Metoda sprawdza czy podany znak jest (

bool ExpectedSymbol::isBracketBegin(const string & bb)
{
	return (bb[0] == '(');
}

/****************************************************************************/
// Metoda sprawdza czy podany znak jest )

bool ExpectedSymbol::isBracketEnd(const string & be)
{
	return (be[0] == ')');
}

/****************************************************************************/
// Metoda sprawdza czy podany znak jest litera

bool ExpectedSymbol::isLetter(const string & c)
{
	return (c[0] >= 'a' && c[0] <= 'z' || c[0] >= 'A' && c[0] <= 'Z');
}


/********************************************************************/
//Metoda odpowiedzalana za stwierdzenie czy dany symbol sie nadaje do 
//danego typu oczekiwanego wydarzenia

bool ExpectedSymbol::check(string c, tokenType expected)
{
	//stworzenie mapy
	unordered_map<tokenType, bool (ExpectedSymbol::*) (const string &)> mymap = { 
		{ NUMBER, &ExpectedSymbol::isNumber },
		{ OPERATOR, &ExpectedSymbol::isOperator },
		{ FUNCTION, &ExpectedSymbol::isFunction },
		{ DOT, &ExpectedSymbol::isDot },
		{ PLUSMINUS, &ExpectedSymbol::isPlusMinus },
		{ WHITE_SPACE, &ExpectedSymbol::isWhiteSpace },
		{ BRACKET_BEGIN, &ExpectedSymbol::isBracketBegin },
		{ BRACKET_END, &ExpectedSymbol::isBracketEnd },
		{ LETTER, &ExpectedSymbol::isLetter }
	};

	if (expected == ANY)
		return true;

	return (this->*mymap[expected])(c);
}
