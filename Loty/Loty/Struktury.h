#include "DetectMemoryLeaks.h"

#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <iostream>

using namespace std;

struct Pasazer {
	string nazwisko;
	int nr_miejsca;
	Pasazer *P_nastepny;				//wskaznik na nastepny element listy pasazerow 
	Pasazer *P_poprzedni;				//wskaznik poprzedni element listy pasazerow
};

struct Lot {
	string symbol_lotu;
	string lotnisko;
	string data;
	Lot *L_nastepny;					//wskaznik na nastepny element listy lotow 
	Lot *L_poprzedni;					//wskaznik poprzedni element listy lotow
	int ile_pasazerow = 0;
	Pasazer *wsk_pasazer_glowa;			//wskaznik na glowe listy pasazerow
	Pasazer *wsk_pasazer_ogon;			//wskaznik na ogon listy pasazerow

};

struct List_Loty_info {
	int liczba_lotow = 0;
	Lot *L_glowa, *L_ogon;				//wskazniki na nastepny i poprzedni element listy lotow
};

#endif