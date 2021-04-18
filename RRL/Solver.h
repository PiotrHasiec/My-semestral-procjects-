/** @file */
#pragma once
#include "Matrix.h"
class Solver///< Abstrakcyjna klasa do rozwiazywania ukladow rownañ
{
protected:

Matrix wyniki;///< Macierz wynikow
public:
	/** wirtualna metoda rozwiazywania rownañ 
	@param[in] A macierz dolaczona Nx(N+1) gdzie lewa czesc NxN jest macierza wspolczynnikow, a ostatni wiersz jest wektorem wynikow rownania w postaci macierzowej*/
	virtual bool solv(Matrix A) = 0;
	Matrix results();//< funkcja zwracajaca macierz wynikow
};


class Solver_i :public Solver///< Abstrakcyjna klasa do iteracyjnego rozwiazywania ukladow rownañ
{
protected:

	bool norm1(Matrix& A);///< 1. Norma zbieznosci metody iteracyjnej 
	bool norm2(Matrix& A);///< 2. Norma zbieznosci metody iteracyjnej 
	bool norm3(Matrix& A);///< 3. Norma zbieznosci metody iteracyjnej 
	double precision = 0.001;///< Precyzja generowania rozwiazania (warunek stopu) 
public:
	/** wirtualna metoda rozwiazywania rownañ
	@param[in] A macierz dolaczona Nx(N+1) gdzie lewa czesc NxN jest macierza wspolczynnikow, a ostatni wiersz jest wektorem wynikow rownania w postaci macierzowej*/
	virtual bool solv(Matrix A) = 0;
	void set_precision(double precision);///< Ustawia precyzje generowania rozwiaznia 
	

};

