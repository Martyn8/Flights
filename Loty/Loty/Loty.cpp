#include "DetectMemoryLeaks.h"

#include <iostream>
#include <string>
#include <fstream>

#include "Funkcje.h"
#include "Struktury.h"

using namespace std;

int main(int ilosc_argumentow, char **tablica_argumentow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	List_Loty_info Lista_Lotow;

	string nazwa_pliku = "";
	if (Sprawdzenie_przelacznika(ilosc_argumentow, tablica_argumentow, nazwa_pliku))
	{
		if (Sprawdzanie_pliku(nazwa_pliku))
		{
			Wczytywanie_danych_z_pliku(nazwa_pliku, Lista_Lotow);
			Sortuj_Pasazerow(Lista_Lotow);
			Tworzenie_plikow(Lista_Lotow);
			Usuwanie_listy_list(Lista_Lotow);
		}
		else
			Pomoc();
	}
	else
		Pomoc();
	
	return 0;
 }