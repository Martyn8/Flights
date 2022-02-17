#include "DetectMemoryLeaks.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Funkcje.h"
#include "Struktury.h"


using namespace std;

void Pomoc()
{
	cout << "*POMOC*" << endl;
	cout << "Wprowadz argumenty w postaci: nazwa_pliku, przelacznik/pzrelaczniki, nazwa_pliku_z_danymi." << endl;
	cout << "Aby uruchomic pomoc wpisz '-h'." << endl;
	cout << "Aby wprowadzic plik wejœciowy z rezerwacjami wpisz '-i'." << endl;
	cout << "Wpisz odpowiednia nazwe pliku" << endl;
	cout << "W przypadku wystapienia bledow podczas dalszej pracy programu prosze poprawic dane w pliku wejsciowym lub wprowadzone argumenty wskazane w wyswitlonym komunikacie." << endl;
}

bool Sprawdzenie_przelacznika(int ilosc_argumentow, char ** tablica_argumentow, string &nazwa_pliku)
{
	short ile_i = 0, ile_h = 0;				//liczniki pzrelacznikow -i -h
	string przelacznik_i = "-i", przelacznik_h = "-h";
	for (int i = 1; i < ilosc_argumentow; i++)
	{
		if (tablica_argumentow[i] == przelacznik_i)				//sprawdzenie ile przelacznikow zostalo wprowadzone
			ile_i++;											//Je¿eli ka¿dy z przelacznikow zostal wprowadzony co najwyzej raz
		if (tablica_argumentow[i] == przelacznik_h)				//funkcja ustala miejsce nazwy pliku w tablicy argumentow
			ile_h++;											// i/lub wyswietla pomoc
	}

	if (ile_i == 1 && ile_h == 0 && ilosc_argumentow == 3)
	{
		nazwa_pliku = tablica_argumentow[2];
		return true;
	}
	else if (ile_h == 1 && ile_i == 1 && ilosc_argumentow == 4)
	{
		nazwa_pliku = tablica_argumentow[3];
		Pomoc();
		return true;
	}
	else if (ile_h == 1 && ile_i == 0 && ilosc_argumentow == 2)
	{
		Pomoc();
	}
	else
	{
		cout << "KOMUNIKAT: Podany przelacznik nie jest prawidlowy." << endl;
		return false;
	}
}

bool Sprawdzenie_kompletnosci_danych(string &linia, int &znak)
//funkcja sprawdza czy w kazdej linii zanjduja sie wszystkie dane poprzez wyliczenie ilosci spacji i porownanie
//jej z minimaln¹ iloscia spacji ktora wynosi 4
{
	while (linia[znak] == ' ')
		znak++;

	int dlugosc = linia.length();
	int ile_spacji=0;

	while (znak != dlugosc)
	{
		if (znak > 1)
		{
			if (linia[znak] == ' ' && (linia[znak + 1] != ' ' && linia[znak - 1] != ' '))
				ile_spacji++;
		}
		else
		{
			if (linia[znak] == ' ' && linia[znak + 1] != ' ')
				ile_spacji++;
		}
		znak++;
	}
	if (ile_spacji < 4)
	{
		cout << "KOMUNIKAT: Dane nie sa kompletne." << endl;
		return false;
	}
	else return true;
}

bool Sprawdzanie_identyfikatora(string &linia, int &znak)
//funkcja sprawdza poprawnosc identyfikatora lotu - kazdy znak identyfikatora powinien byc cyfra lub duza litera
{
	znak = 0;
	while (linia[znak] == ' ')
		znak++;

	for (int i = 0; i < 5; i++)
	{
		if (!((linia[znak + i] >= '0' && linia[znak + i] <= '9') || (linia[znak + i] >= 'A' && linia[znak + i] <= 'Z')))
		{
			cout << "KOMUNIKAT: Identyfikator zawiera nirprawidlowe znaki." << endl;
			return false;
		}
	}
	znak+=6;
}

bool Sprawdzanie_lotniska(string &linia, int &znak)
//funkcja sprawdza poprawnosc lotniska - kazdy znak powinien byc litera gdzie pierwszy znak powinien byc duza litera
{
	while (linia[znak] == ' ')
		znak++;

	int Pierwszy_znak = znak;
	while (linia[znak] != ' ')
	{
		if (znak == Pierwszy_znak)
		{
			if (!(linia[znak] >= 'A' && linia[znak] <= 'Z'))
			{
				cout << "KOMUNIKAT: Lotnisko zaczyna sie na mala litere." << endl;
				return false;
			}
		}
		else
		{
			if (!(linia[znak] >= 'a' && linia[znak] <= 'z'))			
			{
				cout << "KOMUNIKAT: Lotnisko zawiera nirprawidlowe znaki." << endl;
				return false;
			}
		}
		znak++;
	}
	znak++;
}

bool Sprawdzenie_daty(string &linia, int &znak)
//funkcja sprawdza poprawnosc daty lotu - kazdy znak powinien byc cyfra
{
	string rok, miesiac, dzien;
	rok = "";
	miesiac = "";
	dzien = "";

	while (linia[znak] == ' ')
		znak++;

	if (linia[znak] != ' ')
	{
		int i = 0;
		while (linia[znak] != '-')
		{
			if (!(linia[znak] >= '0' && linia[znak] <= '9'))
			{
				cout << "KOMUNIKAT: Rok zawiera nirprawidlowe znaki." << endl;
				return false;
			}
			rok += linia[znak];
			znak++;
			i++;
		}	
		int int_rok = atoi(rok.c_str());		
		znak++;

		int rok_przestepny;
		if (int_rok % 4 == 0 && int_rok % 100 != 0 || int_rok % 400 == 0)
		{
			rok_przestepny = int_rok;
		}

		i = 0;
		while (linia[znak] != '-')
		{
			if (!(linia[znak] >= '0' && linia[znak] <= '9'))
			{
				cout << "KOMUNIKAT: Miesiac zawiera nirprawidlowe znaki." << endl;
				return false;
			}
			miesiac += linia[znak];
			znak++;
			i++;
		}
		int int_miesiac = atoi(miesiac.c_str());
		znak++;

		i = 0;
		while (linia[znak] != ' ')
		{
			if (!(linia[znak] >= '0' && linia[znak] <= '9'))
			{
				cout << "KOMUNIKAT: Dzien zawiera nirprawidlowe znaki." << endl;
				return false;
			}
			dzien+= linia[znak];
			znak++;	
			i++;
		}
		int int_dzien = atoi(dzien.c_str());
		znak++;
		
		if (1 > int_miesiac || int_miesiac > 12)
		{
			cout << "KOMUNIKAT: Nirprawidlowy numer miesiaca." << endl;
			return false;
		}
		if ((int_miesiac == 1 || 3 || 5 || 7 || 8 || 10 || 12) && (1 > int_dzien || int_dzien > 31))
		{
			cout << "KOMUNIKAT: Nirprawidlowy numer dnia miesiaca." << endl;
			return false;
		}
		if ((int_miesiac == 2 && (1 > int_dzien || int_dzien > 28 || (int_rok == rok_przestepny && (1 > int_dzien || int_dzien > 29)))))
		{
			cout << "KOMUNIKAT: Nirprawidlowy numer dnia miesiaca." << endl;
			return false;
		}
		if ((int_miesiac == 4 || 6 || 9 || 11) && (1 > int_dzien || int_dzien > 30))
		{
			cout << "KOMUNIKAT: Nirprawidlowy numer dnia miesiaca." << endl;
			return false;
		}
	}
}

bool Sprawdzenie_nazwiska(string &linia, int &znak)
//funkcja sprawdza poprawnosc nazwiska - kazdy znak powinien byc litera gdzie pierwszy znak powinien byæ duza litera
{
	while (linia[znak] == ' ')
		znak++;

	int Pierwszy_znak = znak;

	while (linia[znak] != ' ')
	{
		if (znak == Pierwszy_znak)
		{
			if (!(linia[znak] >= 'A' && linia[znak] <= 'Z'))
			{
				cout << "KOMUNIKAT: Nazwisko zaczyna sie na mala litere." << endl;
				return false;
			}
		}
		else
		{
			if (!(linia[znak] >= 'a' && linia[znak] <= 'z'))
			{
				cout << "KOMUNIKAT: Nazwisko zawiera nirprawidlowe znaki." << endl;
				return false;
			}
		}
		znak++;
	}
	znak++;
}

bool Sprawdzenie_miejsca(string &linia, int &znak)
//funkcja sprawdza poprawnosc miejsca - kazdy znak powinien byc cyfra
{
	while (linia[znak] == ' ')
		znak++;

	int dlugosc = linia.length();

	while (znak != dlugosc)
	{
		if (!(linia[znak] >= '0' && linia[znak] <= '9'))
		{
			cout << "KOMUNIKAT: Numer miejsca zawiera nirprawidlowe znaki." << endl;
			return false;
		}
		znak++;
	}
}

bool Sprawdzanie_pliku(string &nazwa_pliku)
//funkcja sprawdza czy plik istnieje, czy nie jest pusty i wywoluje funkcje ktore sprawdzaja poprawnosc danych
{
	int znak = 0;				//zmienna okresla miejsce znaku w linii
	ifstream plik;
	plik.open(nazwa_pliku);

	if (plik)
	{
		plik.seekg(0, ios::end);
		if (plik.tellg() == 0)
		{
			cout << "KOMUNIKAT: Plik jest pusty" << endl;
			return false;
		}
		else
		{
			plik.seekg(0);
			while (!plik.eof())
			{
				string linia_oryginalna;
				string linia = "";				//zmieniona linia jedynie z pojedynczymi spacjami
				getline(plik, linia_oryginalna);


				if (linia_oryginalna.empty())
					continue;

				for (int i = 0; i < linia_oryginalna.length() - 1; i++)
					if (!(linia_oryginalna[i] == ' ' && linia_oryginalna[i + 1] == ' '))
					{
						linia += linia_oryginalna[i];
					}
				
				if (!Sprawdzenie_kompletnosci_danych(linia, znak))
					return false;
				if (!Sprawdzanie_identyfikatora(linia, znak))
					return false;
				if (!Sprawdzanie_lotniska(linia, znak))
					return false;
				if (!Sprawdzenie_daty(linia, znak))
					return false;
				if (!Sprawdzenie_nazwiska(linia, znak))
					return false;
				if (!Sprawdzenie_miejsca(linia, znak))
					return false;
				znak = 0;
			}
		}
	}
	else
	{
		cout << "KOMUNIKAT: Nie udalo sie otworzyc pliku" << endl;
		return false;
	}
	plik.close();
}

void Dodaj_Pasazera(List_Loty_info &info, string nazwisko, int nr_miejsca, string symbol_lotu)
{
	Pasazer *pom;				//wskaznik na strukture danych pasazera
	pom = new Pasazer;
	pom->nazwisko = nazwisko;
	pom->nr_miejsca = nr_miejsca;

	Lot *p;				//wskaznik na strukture danych lotu
	p = info.L_glowa;

	while (p->symbol_lotu != symbol_lotu)			//wskaznik p zostaje ustawiony na elemencie listy lotow z odpowiadaj¹cym symbolem lotu
	{
		p = p->L_nastepny;
	}
	if(p->ile_pasazerow==0)				//jezeli do lotu nie ma dopisanych pasazerow wskaznik na glowe listy pasazerow zostaje przypisany do obecnego pasazera
	{
		p->wsk_pasazer_glowa = pom;
		p->wsk_pasazer_ogon = pom;
		pom->P_nastepny = nullptr;
		pom->P_poprzedni = nullptr;
		p->ile_pasazerow++;
	}
	else
	{
		pom->P_nastepny = nullptr;
		pom->P_poprzedni = p->wsk_pasazer_ogon;
		p->wsk_pasazer_ogon->P_nastepny = pom;
		p->wsk_pasazer_ogon = pom;
		p->ile_pasazerow++;
	}
}

void Dodaj_Lot(List_Loty_info &info, string symbol_lotu, string lotnisko, string data)
{
	Lot *pom;				//wskaznik na strukture danych lotu
	pom = new Lot;
	pom->data = data;
	pom->lotnisko = lotnisko;
	pom->symbol_lotu = symbol_lotu;
	
	if (info.liczba_lotow == 0)
	{
		info.L_glowa = pom;
		info.L_ogon = pom;
		pom->L_nastepny = nullptr;
		pom->L_poprzedni = nullptr;
		info.liczba_lotow++;
	}
	else
	{
		pom->L_poprzedni = info.L_ogon;
		pom->L_nastepny = nullptr;
		info.L_ogon->L_nastepny = pom;
		info.L_ogon = pom;
		info.liczba_lotow++;
	}
}

void Znajdz_i_dodaj(List_Loty_info &info, string lotnisko, string data, string symbol_lotu, string nazwisko, int nr_miejsca)
//jesli lista loyow nie jest pusta, funkcja wyszukuje lot z odpowiednim identyfikatorem i przypisuje do niego pasazera
//jesli nie udalo sie znalezc takiego lotu lub lista lotow jest pusta funkcja sprawdza czy jakis lot juz istnieje, 
//jesli nie tworzy nowy lot i dodaje do niego pasazera
{
	if (info.liczba_lotow == 0)
	{
		Dodaj_Lot(info, symbol_lotu, lotnisko, data);
		Dodaj_Pasazera(info, nazwisko, nr_miejsca, symbol_lotu);
	}
	else
	{
		Lot *pom;				//wskaznik na strukture danych lotu
		pom = info.L_glowa;

		while (pom)
		{
			if (pom->symbol_lotu == symbol_lotu)
			{
				Dodaj_Pasazera(info, nazwisko, nr_miejsca, symbol_lotu);	
				break;
			}
			else if (pom == info.L_ogon)
			{
				Dodaj_Lot(info, symbol_lotu, lotnisko, data);
				Dodaj_Pasazera(info, nazwisko, nr_miejsca, symbol_lotu);	
				break;
			}
			pom = pom->L_nastepny;
		}
	}
}

void Wczytywanie_danych_z_pliku(string &nazwa_pliku, List_Loty_info &info)
{
	ifstream plik;
	plik.open(nazwa_pliku);

	string symbol_lotu, lotnisko, data, nazwisko;				//zmienne do przechowywania danych z pliku
	int nr_miejsca;

	while (plik >> symbol_lotu >> lotnisko >> data >> nazwisko >> nr_miejsca)
	{
		Znajdz_i_dodaj(info, lotnisko, data, symbol_lotu, nazwisko, nr_miejsca);
	}

	plik.close();
}

void Dodaj_Prawego_wartownika(List_Loty_info &info, Lot *wsk)
{
	Pasazer *pom;				//wskaznik na strukture danych pasazera
	pom = new Pasazer;
	pom->nazwisko = "prawy wartownik";

	pom->P_nastepny = nullptr;
	wsk->wsk_pasazer_ogon->P_nastepny = pom;
	pom->P_poprzedni = wsk->wsk_pasazer_ogon;
	wsk->wsk_pasazer_ogon = pom;
	wsk->ile_pasazerow++;
}

void Dodaj_Lewego_wartownika(List_Loty_info &info, Lot *wsk)
{
	Pasazer *pom;
	pom = new Pasazer;
	pom->nazwisko = "lewy wartownik";

	pom->P_poprzedni = nullptr;
	pom->P_nastepny = wsk->wsk_pasazer_glowa;
	wsk->wsk_pasazer_glowa->P_poprzedni = pom;
	wsk->wsk_pasazer_glowa = pom;
	wsk->ile_pasazerow++;
}

void Usun_pasazera_z_poczatku(List_Loty_info &info, Lot *wsk)
{
	Pasazer *pom;				//wskaznik na strukture danych pasazera
	pom = wsk->wsk_pasazer_glowa;

	if (wsk->ile_pasazerow > 1)
	{		
		wsk->wsk_pasazer_glowa = pom->P_nastepny;
		pom->P_nastepny->P_poprzedni = nullptr;
		pom->P_nastepny = nullptr;
		delete pom;
		wsk->ile_pasazerow--;
	}
	else
	{
		delete pom;
		wsk->ile_pasazerow;
	}
};

void Usun_Pasazera_z_konca(List_Loty_info &info, Lot *wsk)
{
	Pasazer *pom;				//wskaznik na strukture danych pasazera
	pom = wsk->wsk_pasazer_ogon;

	if (wsk->ile_pasazerow > 1)
	{
		wsk->wsk_pasazer_ogon = pom->P_poprzedni;
		pom->P_poprzedni->P_nastepny = nullptr;
		pom->P_poprzedni = nullptr;
		delete pom;
		wsk->ile_pasazerow--;
	}
	else
	{
		delete pom;
		wsk->ile_pasazerow--;
	}
}

void Partycje(Pasazer *lw, Pasazer *pw)
{
	Pasazer *q, *pom;				//wskazniki na strukture danych pasazera
	Pasazer *piwot;					//wskazniki na element wg ktorego wstepnie sortujemy dane
	piwot = lw->P_nastepny;
	q = piwot->P_nastepny;
	if (q != pw)
	{
		while (q != pw)
		{
			pom = q;
			q = q->P_nastepny;
			if (pom->nr_miejsca < piwot->nr_miejsca)
			{
				pom->P_poprzedni->P_nastepny = pom->P_nastepny;
				pom->P_nastepny->P_poprzedni = pom->P_poprzedni;
				pom->P_nastepny = piwot;
				pom->P_poprzedni = piwot->P_poprzedni;
				piwot->P_poprzedni = pom;
				pom->P_poprzedni->P_nastepny = pom;
			}
		}
		if (lw->P_nastepny != piwot) Partycje(lw, piwot);
		if (piwot->P_nastepny != pw) Partycje(piwot, pw);
	}
}

void Sortuj_Pasazerow(List_Loty_info &info)
//sortowanie listy pasazerow z uzyciem metody szybkiego sortowania
{
	Lot *p;				//wskaznik na strukture danych lotu
	p = info.L_glowa;

	while (p != nullptr)
	{
		if (p->ile_pasazerow > 1)
		{

			Dodaj_Prawego_wartownika(info, p);
			Dodaj_Lewego_wartownika(info, p);

			Partycje(p->wsk_pasazer_glowa, p->wsk_pasazer_ogon);

			Usun_pasazera_z_poczatku(info, p);
			Usun_Pasazera_z_konca(info, p);
		}
		p = p->L_nastepny;
	}
}

void Tworzenie_plikow(List_Loty_info info)
//funkcja tworzy pliki o nazwie symbolu lotu, wpisuje do nich symbol lotu,
//lotnisko, date i liste pasazerow oraz liczy ile pasazerow jest dla danego lotu
{
	string nazwa_pliku;
	Lot *p;					//wskaznik na strukture danych lotu
	p = info.L_glowa;
	Pasazer *q;				//wskaznik na strukture danych pasazera

	while (p != nullptr)
	{
		nazwa_pliku = p->symbol_lotu + ".txt";
		ofstream plik_zewnetrzny;
		plik_zewnetrzny.open(nazwa_pliku, ios_base::out);

		if (plik_zewnetrzny.is_open())
		{
			plik_zewnetrzny << "Symbol lotu: " << p->symbol_lotu << endl;
			plik_zewnetrzny << "Lotnisko: " << p->lotnisko << endl;
			plik_zewnetrzny << "Data lotu: " << p->data << endl << endl;
			plik_zewnetrzny << "Lista pasazerow:" << endl;

			q = p->wsk_pasazer_glowa;

			while (q != nullptr)
			{
				plik_zewnetrzny << q->nr_miejsca << " " << q->nazwisko << endl;
				q = q->P_nastepny;
			}
			plik_zewnetrzny << endl << "Liczba rezerwacji: " << p->ile_pasazerow << endl;
			p = p->L_nastepny;
			plik_zewnetrzny.close();
		}
	}
}

void Usun_Lot(List_Loty_info &info, Lot *pom)
{
	pom = info.L_glowa;
	if (info.liczba_lotow > 0)
	{
		if (info.liczba_lotow > 1)
		{
			info.L_glowa = pom->L_nastepny;
			pom->L_nastepny->L_poprzedni = nullptr;
			pom->L_nastepny = nullptr;
			delete pom;
			info.liczba_lotow--;
		}
		else
		{
			delete pom;
			info.liczba_lotow--;
		}
	}
}

void Usuwanie_listy_list(List_Loty_info &info)
{
	Lot *pom;				//wskaznik na strukture danych lotu
	
	while (info.liczba_lotow != 0)
	{
		pom = info.L_glowa;

		while (pom->ile_pasazerow != 0)
		{
			Usun_Pasazera_z_konca(info, pom);
		}
		Usun_Lot(info, pom);
	}
}

