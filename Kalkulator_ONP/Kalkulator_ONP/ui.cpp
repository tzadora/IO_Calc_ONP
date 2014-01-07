#include <iostream>
#include "ui.h"

using namespace std;

//Klasa odpowiadajaca za interfejs uzytkownika
/********************************************************************/
//konstruktor ustawia wielkosc bufora

UserInterface::UserInterface(int size) : max_buffer_size(size)
{
	;
}

/********************************************************************/
//Metoda odpowiadajaca za przywitanie

void UserInterface::welcome()
{
	cout << "Witam w kalkulatorze opartym na ONP - wpisz wyrazenie, ktore chcesz policzyc:" << endl;
}

/********************************************************************/
//Metoda odpowiadajaca za wczytanie stringa od usera

void UserInterface::loadBuffer(char* buffer)
{
	cin.getline(buffer, max_buffer_size);
}

/********************************************************************/
//Metoda odpowiadajaca za wyswietlenie wyniku

void UserInterface::showResult(double result)
{
	cout << " = " << result << endl;
}

/********************************************************************/
//Metoda odpowiadajaca za spytanie czy user chce wiecej obliczen

bool UserInterface::wantMoreCalculation()
{
	char c;
	cout << "Nastepne obliczenie? [T/N]" << endl;
	cin.get(c);
	cin.get();		//zeby nie przeskakiwalo od razu 
	if (c != 'n' && c != 'N')
		return true;
	else
		return false;
}
