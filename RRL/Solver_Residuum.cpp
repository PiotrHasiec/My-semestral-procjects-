/** @file */
#include "Solver_Residuum.h"
#include <algorithm>
#include <iostream>
double Solver_Residuum::residuum(int& r, Matrix& a, Matrix& b)
{
	double returnn = 0;
	for (int i = 0; i < a.size_y(); i++)
	{
		returnn += a[r][i] * b[0][i];
	}
	returnn += a[r][a.size_x() - 1];
	return returnn;
}
bool Solver_Residuum::solv(Matrix A)
{
	if (norm1(A) || norm2(A) || norm3(A))// jesli co najmniej jedna norma jest spelniona
	{
		const int n = A.size_y();
		int max = 0;
		Matrix x{ n,1 };
		Matrix r{ n,1 };
		wyniki.set_d(A.size_y(), 1);
		for (int i = 0; i < n; i++)
		{
			x[i][0] = A[i][n] / A[i][i];
			r[i][0] = 0;
		}

		for (int i = 0; i < n; i++)
		{
			double a = A[i][i];
			A[i][n] /= a;

			for (int j = 0; j < n; j++)
			{
				A[i][j] /= -a;
				r[i][0] += A[i][j] * x[j][0];
			}
			r[i][0] += A[i][n];
		}
			bool stop = 1;
			int i = 0;
		for (i=0; stop; i++)
		{
			wyniki = x;
			stop = max = 0;
			for (int j = 1; j < n; j++)
			{
				if (abs(r[max][0]) < abs(r[j][0]))
				{
					max = j;
				}
			}


			x[max][0] += r[max][0];

			for (int j = 0; j < n; j++)
			{
				if (j != max)
					r[j][0] += r[max][0] * A[j][max];

				if ((abs(x[j][0] - wyniki[j][0]) > precision))
				{
					stop = 1;
				}
			}
			r[max][0] = 0;

		
		}
		
		wyniki = x;
		return true;
	}
	return false;
}