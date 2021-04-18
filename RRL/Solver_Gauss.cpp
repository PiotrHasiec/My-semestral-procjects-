/** @file */
#include "Solver_Gauss.h"
bool Solver_Gauss::solv(Matrix A)
{
	wyniki.set_d(A.size_y(), 1);
	int n = A.size_y();
	long double a;

	for (int i = 1; i < n; i++)//n-1 eliminacji
	{
		for (int j = i; j < n; j++)//pojedyñcza eliminacja gaussa
		{
			if (A[i - 1][i - 1] == 0)//usuwanie 0 z glownej przekatnej
			{
				for (int o = i; o < n; o++)
				{
					A.swap_y(i - 1, o);
					if (A[i - 1][i - 1] != 0)
						break;

				}
				if (A[i - 1][i - 1] == 0)
					return false;
			}

			a = -A[j][i - 1] / A[i - 1][i - 1];//obliczanie skladnuka eliminujacego  ita zmienna
			for (int k = i - 1; k < n + 1; k++)
			{
				A[j][k] += a * A[(i - 1)][k];

			}

		}
		A.print(4, 9); std::cout <<std:: endl;

	}

	wyniki[n - 1][0] = A[n - 1][n] / A[n - 1][n - 1];
	for (int i = n - 2; i >= 0; i--)//podstawianie
	{
		wyniki[i][0] = A[i][n];
		for (int j = n - 1; j > i; j--)
		{

			wyniki[i][0] -= A[i][j] * wyniki[j][0];
		}
		if (A[i][i] == 0)
		{
			return 0;
		}
		wyniki[i][0] = (wyniki[i][0]) / A[i][i];
	}


	return 1;

}