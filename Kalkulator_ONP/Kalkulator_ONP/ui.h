#pragma once

//klasa opisujaca user-interface 
class UserInterface
{
private:
	const int max_buffer_size;

public:
	UserInterface(int size);			//konstruktor ustawia wielkosc bufora

	void welcome();						//metoda odpowiadajaca za przywitanie
	void loadBuffer(char* buffer);		//metoda odpowiadajaca za wczytanie stringa od usera
	void showResult(double result);		//metoda odpowiadajaca za wyswietlenie wyniku
	bool wantMoreCalculation();			//metoda odpowiadajaca za spytanie czy user chce wiecej obliczen
};
