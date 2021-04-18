/** @file */
#define _CRTDBG_MAP_ALLOC
#include <string>
#include <clocale>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Funkcje.h" 

using namespace std;


int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	setlocale(LC_ALL, "");
	vertex* węzeł = nullptr;
	string oname;
	string iname;
	int liczba_wierzchołków;
	long double** matrix ;
	vertex* pgłowa;

	for (int i = 0; i < argc; i++)//obsługa parametrów programu
	{

		if ((string)argv[i] == "-i" and i + 1 < argc)
		{
			iname = argv[++i];
		}
		if ((string)argv[i] == "-o" and i + 1 < argc)
		{
			oname = argv[++i];
		}
		

	}
	
	if (not (iname.empty() or oname.empty()))
	{


		
		if (not download(iname, węzeł))// Jeśli nie udało się pobranie danych lub zostało przerwane, zwolnij pamięć i zakończ program 
		{
			delete_vertices_forend_r(węzeł);
			return 0;
		}
		
		sort(węzeł);//nie trzeba tego używać. To tylko dla estetyki 
		liczba_wierzchołków = count(węzeł);//Sprawdzenie liczby wierzchołków
		matrix = makematrix(węzeł);//utworzenie układu równań, pamiętać o zwolnieniu
		
		pgłowa = węzeł;

	
		
		if (not matrix)
		{
			delete_vertices_forend_r(węzeł);
			return 0;
		}
	
		if (gauss(matrix, liczba_wierzchołków))
		{
			for (int i = 0; i <= liczba_wierzchołków - 2 and pgłowa; i++)//wstawianie wartości potencjałów wierzchołków do listy
			{
				pgłowa->potential = matrix[i][liczba_wierzchołków - 1];
				pgłowa = pgłowa->nextvertex;
			}
			pgłowa = nullptr;

			generuj_prądy_w_gałęziach(węzeł);
			save(oname, węzeł);

		}
		
		for (int i = 0; i < liczba_wierzchołków - 1; i++)//usuwanie zaalokowanej tablicy
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		
		delete_vertices_forend_r(węzeł);
		return 0;
	}
	else
	{
		cout << "Brak nazyw pliku wyjśiowego i/lub wyjściowego" << endl;
	}
	
}
