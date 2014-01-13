#pragma once

#include "ExpectedSymbol.h"

enum tokenType;
// Klasa przechowujaca symbole wpisane przez uzytkownika

class Symbol
{
private:
	tokenType type;								//Typ wyrazenia
	double(*fun)(double);						//Opcjonalny wskaznik do funkcji obliczajacej
	
	double(Symbol::*fun2)(double, double);		//Opcjonalny wskaznik do funkcji obliczajacej
						
	std::string content;						//Zawartosc symbolu		
	int priority;								//priorytet operatora


	//funkcje pomocnicze
	void setIfOperator();				//ustawia parametry operatora
	void setIfFunction();				//ustawia parametry funkcji

	//funkcje do operatorow
	double addition(double, double);
	double subtraction(double, double);
	double multiplication(double, double);
	double division(double, double);
	double exponentiation(double, double);
	
public:
	Symbol();
	Symbol(std::string content, tokenType tt);
	std::string showSymbol();
	tokenType getType();
	double(*getFun())(double);
	double(Symbol::*getFun2())(double, double);
	int getPriority();					
};
