/** @file */
#include "Solver_Seidl.h"
#include <algorithm>
#include <iostream>
bool Solver_Seidl::solv(Matrix A)
{
	if (norm1(A) || norm2(A) || norm3(A))// jesli co najmniej jedna norma jest spelniona
	{
		wyniki.set_d(A.size_y(), 1); //Ustawienia rozmiaru macierzy wynikow na odpowiedni
		Matrix x_i{ A.size_y(),2 };
		Matrix a{ A.size_x(), 1 };
		double m = 0;
		for (int i = 0; i < A.size_y(); i++)//przeksztalcamy macierz do wygodniejszej postaci
		{
			a[i][0] = A[i][i];
			A[i][i] = 0;

			for (int j = 0; j < A.size_y(); j++)
			{

				A[i][j] /= -a[i][0];

			}
		}
		bool stop = 1;


		int k = 0;
		for (k = 0; stop; k++)//kazdy przebieg petli to kolejne przyblizenie wektora zmiennych
		{
			stop = 0;
			for (int i = 0; i < A.size_y(); i++)
			{
				x_i[i][0] = A[i][A.size_y()] / a[i][0];// ze wzoru 

				for (int j = 0; j < A.size_y(); j++)// przybliza ita zmienna z uwzglednieniem wylicznych juz w tej operacji
				{
					x_i[i][0] += (x_i[j][0] * A[i][j]);
				}

				if ((abs(x_i[i][0] - x_i[i][1]) > precision))//warunek stopu
				{
					stop = 1;
				}

			}
			for (int l = 0; l < A.size_y(); l++)
				x_i[l][1] = x_i[l][0];

		}
		
		for (int i = 0; i < A.size_y(); i++)
			wyniki[i][0] = x_i[i][k % 2];
		

		return true;
	}
	else
		return false;
}