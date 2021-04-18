/** @file */
#include "Solver.h"
#include <algorithm>
bool Solver_i::norm1(Matrix& A)
{
	double tmp_suma = 0;
	for (int i = 0; i < A.size_y(); i++)// sprawdza silna dominacje w wierszach
	{
		tmp_suma = 0;
		for (int j = 0; j < A.size_y(); j++)
		{
			if (i != j)
				tmp_suma += abs(A[i][j] / A[i][i]);
		}
		if (tmp_suma > 1)
			return 0;
	}
	return 1;
}

bool Solver_i::norm2(Matrix& A)// sprawdza silna dominacje w kolumnach
{
	double tmp_suma = 0;
	for (int i = 0; i < A.size_y(); i++)
	{
		tmp_suma = 0;
		for (int j = 0; j < A.size_y(); j++)
		{
			if (i != j)
				tmp_suma += abs(A[j][i] / A[i][i]);
		}
		if (tmp_suma > 1)
			return 0;
	}
	return 1;
}

bool Solver_i::norm3(Matrix& A)
{
	double tmp = 0;
	for (int i = 0; i < A.size_y(); i++)//zlicza sume kwadratow elementow poza glowna przekatna i sprawdza czy jest mnniejsza od 1
	{
		
		for (int j = 0; j < A.size_y(); j++)
		{
			if (i != j)
				tmp += (A[j][i] / A[i][i])* (A[j][i] / A[i][i]);
		}
			if (tmp > 1)
			return 0;
	}

	return 1;
}

void Solver_i::set_precision(double precision)
{
	this->precision =  precision;
}

Matrix Solver::results()
{
	return wyniki;
}
