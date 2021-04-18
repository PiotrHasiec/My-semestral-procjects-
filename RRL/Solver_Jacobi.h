/** @file */
#pragma once
#include "Solver.h"
#include "Matrix.h"
class Solver_Jacobi : public Solver_i///<Odpowiada za rozwiazywanie ukladow rownañ metoda Jacobiego
{
public:
	/** Implementacja metody rozwiazywania rownañ metoda Jacobiego
	@param[in] A macierz dolaczona Nx(N+1) gdzie lewa czesc NxN jest macierza wspolczynnikow, a ostatni wiersz jest wektorem wynikow rownania w postaci macierzowej*/
	bool solv(Matrix A);
};
