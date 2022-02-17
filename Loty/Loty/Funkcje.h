#include "DetectMemoryLeaks.h"

#ifndef FUNKCJA_H
#define FUNKCJA_H

#include <iostream>
#include <string>

#include "Struktury.h"



using namespace std;

/* Funkcja wyswietla pomoc*/
void Pomoc();

/*Funkcja sprawdza czy w konsoli zostaly wprowadzone poprawne przelaczniki*/
bool Sprawdzenie_przelacznika(int ilosc_argumentow, char **tablica_argumentow, string &nazwa_pliku);

/*Funkcja sprawdza czy plik istnieje i czy dane sa poprawne*/
bool Sprawdzanie_pliku(string &nazwa_pliku);

/*Funkcja sprawdza czy w danej linii sa wszystkie dane*/
bool Sprawdzenie_kompletnosci_danych(string &linia, int &znak);

/*Funkcja sprawdza czy identyfikator lotu jest poprawny*/
bool Sprawdzanie_identyfikatora(string &linia, int &znak);

/*Funkcja sprawdza czy nazwa lotniska startowego jest poprawna*/
bool Sprawdzanie_lotniska(string &linia, int &znak);

/*Funkcja sprawdza czy data lotu jest poprawna*/
bool Sprawdzenie_daty(string &linia, int &znak);

/*Funkcja sprawdza czy nazwisko pasazera jest poprawne*/
bool Sprawdzenie_nazwiska(string &linia, int &znak);

/*Funkcja sprawdza czy miejsce na ktorym siedzi pasazer jest poprawne*/
bool Sprawdzenie_miejsca(string &linia, int &znak);

/*Funkcja dodaje pasazera na koniec listy pasazerow*/
void Dodaj_Pasazera(List_Loty_info &info, string nazwisko, int nr_miejsca, string symbol_lotu);

/*Funkcja dodaje lot na koniec listy lotow*/
void Dodaj_Lot(List_Loty_info &info, string symbol_lotu, string lotnisko, string data);

/*Funkcja znajduje odpowiedni lot i dodaje do niego pasazera na koniec listy pasazerow*/
void Znajdz_i_dodaj(List_Loty_info &info, string lotnisko, string data, string symbol_lotu, string nazwisko, int nr_miejsca);

/*Funkcja wczytuje dane z pliku*/
void Wczytywanie_danych_z_pliku(string &nazwa_pliku, List_Loty_info &info);

/*Funkcja dodaje wartownika na koniec listy pasazerow*/
void Dodaj_Prawego_wartownika(List_Loty_info &info, Lot *wsk);

/*Funkcja dodaje wartownika na poczatek listy pasazerow*/
void Dodaj_Lewego_wartownika(List_Loty_info &info, Lot *wsk);

/*Funkcja usuwa pasazera z poczatku listy pasazerow*/
void Usun_pasazera_z_poczatku(List_Loty_info &info, Lot *wsk);

/*Funkcja usuwa pasazera z konca listy pasazerow*/
void Usun_Pasazera_z_konca(List_Loty_info &info, Lot *wsk);

/*Funkcja dzieli liste psazerow na partycje*/
void Partycje(Pasazer *lw, Pasazer *pw);

/*Funkcja sortuje liste pasazerow*/
void Sortuj_Pasazerow(List_Loty_info &info);

/*Funkcja tworzy pliki o nazwie identyfikatora lotu z lista pasazerow*/
void Tworzenie_plikow(List_Loty_info info);

/*Funkcja usuwa lot z poczatku listy lotow*/
void Usun_Lot(List_Loty_info &info, Lot *pom);

/*Funkcja usuwa wszystkich pasazerow z danego lotu i nastepnie ten lot*/
void Usuwanie_listy_list(List_Loty_info &info);

#endif // !FUNKCJA_H