/** @file */
#pragma once
#include "Solver.h"
#include "Matrix.h"
class Solver_Gauss : public Solver///<Odpowiada za rozwiazywanie ukladow rownañ metoda Gaussa
{
public:
	/** Implementacja metody rozwiazywania rownañ metoda Gaussa
	@param[in] A macierz dolaczona Nx(N+1) gdzie lewa czesc NxN jest macierza wspolczynnikow, a ostatni wiersz jest wektorem wynikow rownania w postaci macierzowej*/
	bool solv(Matrix A);
};
