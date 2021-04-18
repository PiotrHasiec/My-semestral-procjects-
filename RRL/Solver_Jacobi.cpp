/** @file */
#include "Solver_Jacobi.h"
#include <algorithm>
#include <iostream>
bool Solver_Jacobi::solv(Matrix A)
{
	if (norm1(A) || norm2(A) || norm3(A))// jesli conajmniej jedna norma jest spelniona
	{
		wyniki.set_d(A.size_y(), 1);//Ustawienia rozmiaru macierzy wynikow na odpowiedni
		Matrix x{ 2,A.size_y() };
		Matrix a{ 1, A.size_x() };
		double m = 0;
		for (int i = 0; i < A.size_y(); i++)//przeksztalcamy macierz do wygodniejszej postaci
		{
			a[0][i] = A[i][i];
			A[i][i] = 0;

			for (int j = 0; j < A.size_y(); j++)
			{

				A[i][j] /= -a[0][i];

			}
		}
		bool stop = 1;
		
		int k = 0;
		for (k = 0; stop; k++)
		{
			stop = 0;
			for (int i = 0; i < A.size_y(); i++)//kazdy przebieg petli to kolejne przyblizenie wektora zmiennych
			{
				x[k % 2][i] = A[i][A.size_y()] / a[0][i];// ze wzoru 
				for (int j = 0; j < A.size_y(); j++)// przybliza ita zmienna nie uwzgledniajac tych wyliczonych w tej iteracji
				{
					 x[k % 2][i] += (x[(k + 1) % 2][j] * A[i][j]);
				}
				double tmp = (abs(x[k % 2][i] - x[(k + 1) % 2][i]));
				if ( tmp > precision*10)//warunek stopu
				{
					stop = 1;
				}

			}
			//if (k >2*A.size_x() )
				//stop = 0;
			
		}
		for (int i = 0; i < A.size_y(); i++)
			wyniki[i][0] = x[k % 2][i];
		return true;
	}
	return false;

}