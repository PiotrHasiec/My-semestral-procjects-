/** @file */
#pragma once
#include "Solver.h"
#include "Matrix.h"
class Solver_Residuum : public Solver_i///<Odpowiada za rozwiazywanie ukladow rownañ metoda minimalizacji residuow
{
	/**Pomocnicza metoda oblicznia residuow
	*/
	double residuum(int& c, Matrix& a, Matrix& b);
public:
	/** Implementacja metody rozwiazywania rownañ metoda residuow
	@param[in] A macierz dolaczona Nx(N+1) gdzie lewa czesc NxN jest macierza wspolczynnikow, a ostatni wiersz jest wektorem wynikow rownania w postaci macierzowej*/
	bool solv(Matrix A);

};

