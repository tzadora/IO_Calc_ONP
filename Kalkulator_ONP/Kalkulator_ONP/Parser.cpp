#include <iostream>
#include <string.h>
#include <cctype>
#include "Parser.h"

using namespace std;

/********************************************************************/

Parser::Parser(const string & expression, list<Symbol> & symbols) : expression(expression), listOfSymbols(symbols)
{
	//ustaweienie stanow poczatkowych parsera
	buffer = "";
	state = START;
	errorMessage = "";
	numberOfMissingBraces = 0;
	lastChar = false;
	canEnd = true;
}

/********************************************************************/
/********************************************************************/
/*
* Funkcja parsujaca dajaca mozliwosc przerobienia stringa wpisanego przez
* uzytkownika na liste obiektow klasy Symbol
*/
bool Parser::parse() {

	listOfSymbols.clear();

	for (unsigned i = 0; i < expression.length(); i++)
	{
		//czytamy 1 znak
		c = expression[i];
		//sprawdzamy czy znak nie jest ostatnim
		if (i + 1 == expression.length())
			lastChar = true;

		switch (state)
		{
		case START:
			startState();
			break;

		case READ_NUMBER:
			readNumberState();
			break;

		case READ_NUMBER_BEFORE_DOT:
			readNumberBeforeDotState();
			break;

		case READ_NUMBER_AFTER_DOT:
			readNumberAfterDotState();
			break;

		case READ_FUNCTION:
			readFunctionState();
			break;

		case READ_OPERATOR:
			readOperatorState();
			break;
		}

		//wychwytuje ewentualne bledy **** ERROR ****
		if (state == ERROR || lastChar && (!canEnd || numberOfMissingBraces != 0))
		{
			errorState();
			return false;
		}
	}

	return true;
}


/********************************************************************/
//METODY DZIALAJACE W POSZCZEGOLNYCH STANACH PARSERA
/********************************************************************/
//Metoda dzialajaca gdy parser jest w stanie START

void Parser::startState()
{
	//czyscimy bufor
	buffer = "";
	if (chceckingSystem.check(c, WHITE_SPACE))
		return;

	if (chceckingSystem.check(c, NUMBER))
		actionNumber();

	else if (chceckingSystem.check(c, PLUSMINUS))
		actionPlusMinus();

	else if (chceckingSystem.check(c, BRACKET_BEGIN))
		actionBracketBegin();

	else if (chceckingSystem.check(c, LETTER))
		actionLetter();

	else
		actionError("Blad skladni");
}

/********************************************************************/
//Metoda dzialajaca gdy parser jest w stanie READ_NUMBER

void Parser::readNumberState()
{
	//sprawdzamy jakiego typu jest symbol
	if (chceckingSystem.check(c, NUMBER))
		actionNumber();
	
	else
		actionError("B³¹d sk³adni");
}

/********************************************************************/
//Metoda dzialajaca gdy parser jest w stanie READ_NUMBER_BEFORE_DOT

void Parser::readNumberBeforeDotState()
{
	//sprawdzamy jakiego typu jest symbol
	if (chceckingSystem.check(c, NUMBER))
		actionNumber();
	
	else if (chceckingSystem.check(c, DOT))
		actionNumberAfterDot();
	
	else if (chceckingSystem.check(c, OPERATOR))
		actionOperatorAfterNumber();

	else if (chceckingSystem.check(c, BRACKET_END))
		actionBracketEndAfterNumber();

	else if (chceckingSystem.check(c, WHITE_SPACE))
		actionWhiteSpaceAfterNumber();
		
	else
		actionError("B³¹d sk³adni");
}

/********************************************************************/
//Metoda dzialajaca gdy parser jest w stanie READ_NUMBER_AFTER_DOT

void Parser::readNumberAfterDotState()
{
	//sprawdzamy jakiego typu jest symbol
	if (chceckingSystem.check(c, NUMBER))
		actionNumberAfterDot();
	
	else if (chceckingSystem.check(c, OPERATOR))
		actionOperatorAfterNumber();

	else if (chceckingSystem.check(c, BRACKET_END))
		actionBracketEndAfterNumber();

	else if (chceckingSystem.check(c, WHITE_SPACE))
			actionWhiteSpaceAfterNumber();
		
	//jesli po cyfrze zaraz pojawia sie litera
	else
		actionError("B³¹d sk³adni");
}

/********************************************************************/
//Metoda dzialajaca gdy parser jest w stanie READ_FUNCTION

void Parser::readFunctionState()
{
	if (!chceckingSystem.check(c, BRACKET_BEGIN))
		actionExpectedFunction();
	
	//jesli jest nawias poczatkowy 
	else if (chceckingSystem.check(buffer, FUNCTION))
			actionFunction();
}

/********************************************************************/
//Metoda dzialajaca gdy parser jest w stanie READ_OPERATOR

void Parser::readOperatorState()
{
	//jesli odstep
	if (chceckingSystem.check(c, WHITE_SPACE))
		return;

	if (chceckingSystem.check(c, OPERATOR))
		actionOperator();

	else if (chceckingSystem.check(c, BRACKET_END))
		actionBracketEnd();

	else
		actionError("B³¹d sk³adni");
}

/********************************************************************/
//Metoda dzialajaca gdy parser jest w stanie ERROR

void Parser::errorState()
{
	if (numberOfMissingBraces != 0)
		errorMessage = "Brak parzystosci nawiasow";

	if (!canEnd)
		errorMessage += "\nNieoczekiwany koniec wyrazenia";

	cerr << errorMessage.c_str() << endl;
}


/********************************************************************/
//METODY UZYWANE PRZEZ STANY PARSERA
/********************************************************************/

//Metoda dotyczaca akcji na wystapienie numeru

void Parser::actionNumber()
{
	state = READ_NUMBER_BEFORE_DOT;
	canEnd = true;
	buffer += c;

	if (lastChar)
	{
		listOfSymbols.push_back(Symbol(buffer, NUMBER));
	}
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie numeru po kropce

void Parser::actionNumberAfterDot()
{
	buffer += c;
	state = READ_NUMBER_AFTER_DOT;

	if (lastChar)
	{
		listOfSymbols.push_back(Symbol(buffer, NUMBER));
	}
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie operatora

void Parser::actionOperator()
{
	listOfSymbols.push_back(Symbol(c, OPERATOR));
	state = START;
	canEnd = false;
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie operatora bezposrednio po liczbie

void Parser::actionOperatorAfterNumber()
{
	Symbol s1(buffer, NUMBER);
	listOfSymbols.push_back(s1);
	actionOperator();
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie funkcji

void Parser::actionFunction()
{
	canEnd = false;
	listOfSymbols.push_back(Symbol(buffer, FUNCTION));
	listOfSymbols.push_back(Symbol("(", BRACKET_BEGIN));
	numberOfMissingBraces++;
	state = START;			
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie nawiasu (

void Parser::actionBracketBegin()
{
	listOfSymbols.push_back(Symbol("(", BRACKET_BEGIN));
	numberOfMissingBraces++;
	canEnd = false;
	//nie zmieniamy statusu zostaje dalej start
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie nawiasu )

void Parser::actionBracketEnd()
{
	listOfSymbols.push_back(Symbol(c, BRACKET_END));
	numberOfMissingBraces--;
	state = READ_OPERATOR;
	canEnd = true;
	//nie zmieniamy stanu - READ_OPERATOR
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie nawiasu ) bezposrednio po liczbie

void Parser::actionBracketEndAfterNumber()
{
	listOfSymbols.push_back(Symbol(buffer, NUMBER));
	actionBracketEnd();
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie znaku przed liczba +-

void Parser::actionPlusMinus()
{
	if (c[0] == '+')
		canEnd = false;
	else
	{
		buffer = c;
		canEnd = false;
	}
	state = READ_NUMBER;
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie bialego znaku po liczbie

void Parser::actionWhiteSpaceAfterNumber()
{
	listOfSymbols.push_back(Symbol(buffer, NUMBER));
	state = READ_OPERATOR;
	canEnd = true;
}

/********************************************************************/
//Metoda dotyczaca akcji na wystapienie znaku - litery

void Parser::actionLetter()
{
	buffer = c;
	state = READ_FUNCTION;
	canEnd = false;
}

/********************************************************************/
//Metoda dotyczaca akcji oczekiwania na nazwe funkcji

void Parser::actionExpectedFunction()
{
	buffer += c;
	if (buffer.length() > 4)
		actionError("Zla nazwa funkcji");
}

/********************************************************************/
//Metoda dotyczaca akcji wystapienia bledu 

void Parser::actionError(const std::string & str)
{
	state = ERROR;
	errorMessage = str;
}

/********************************************************************/
