#pragma warning(disable : 4996)

#include <iostream>
#include <conio.h>
#include "rpn.h"
#include "ui.h"

using namespace std;

#define MAX_BUFFER_SIZE 500

int main() 
{
	for (;;)
	{
		//stworzenie bufora o podanym rozmiarze
		char buffer[MAX_BUFFER_SIZE];

		//wyswietlenie komunikatow i wczytanie danych od uzytkownika
		UserInterface ui(MAX_BUFFER_SIZE);
		ui.welcome();
		ui.loadBuffer(buffer);

		//przygotowanie pod onp
		string expression = buffer;
		ReversePolishNotation rpn;

		//obliczenie i wyswietlenie wyniku
		ui.showResult(rpn.calculate(expression));

		if (ui.wantMoreCalculation())
			continue;
		else
			break;
	}
	return 0;
}
