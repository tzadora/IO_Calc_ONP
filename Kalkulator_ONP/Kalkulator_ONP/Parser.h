#pragma once

#include <list>
#include "Symbol.h"

/*
*Klasa dajaca mozliwosc parsowania danych wpisanych przez uzytkownika
*jako string do postaci listy obiektow klasy symbol 
*/

class Parser
{
private:
	//stany parsera
	enum parser_state {
		START,
		READ_NUMBER,
		READ_NUMBER_BEFORE_DOT,
		READ_NUMBER_AFTER_DOT,
		READ_FUNCTION,
		READ_OPERATOR,
		ERROR
	};
	
	const std::string & expression;			//wprowadzony przez usera string
	std::list<Symbol> & listOfSymbols;		//lista symboli 
	std::string c;							//Obecnie czytany znak
	std::string buffer = "";				//Bufor na tymczasowy symbol
	parser_state state = START;				//Obecny stan parsera

	std::string errorMessage = "";			//ewentualna wiadomosc o bledzie 
	int numberOfMissingBraces = 0;			//liczba brakujacych nawiasow zamykajacych , jesli 0 to nie brakuje zadnego
	bool lastChar = false;					//ostatni znak wyrazenia 
	bool canEnd = true;						//czy string moze sie tak skonczyc

	ExpectedSymbol chceckingSystem;			//system sprawdzajacy
	
	//stany parsera - funkcje ktore sie nimi zajmuja
	void startState();
	void readNumberState();
	void readNumberBeforeDotState();
	void readNumberAfterDotState();
	void readFunctionState();
	void readOperatorState();
	void errorState();

	//funkcje z ktorych korzystaja stany parsera
	void actionNumber();
	void actionNumberAfterDot();
	void actionOperator();
	void actionOperatorAfterNumber();
	void actionFunction();
	void actionBracketBegin();
	void actionBracketEnd();
	void actionBracketEndAfterNumber();
	void actionWhiteSpaceAfterNumber();
	void actionPlusMinus();
	void actionLetter();
	void actionExpectedFunction();
	void actionError(const std::string & str);

public:
	//glowna funkcja parsujaca
	bool parse();

	Parser(const std::string & expression, std::list<Symbol> & s);
};
