/** @file */
#include "Matrix.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <random>
#include <ctime>
Matrix::Matrix()
{
	m = 0;
	x = y = c_x = c_y = 0;

}

Matrix::Matrix(int a, int b)
{
	y = a;
	x = b;
	c_x =  x;
	c_y =  y;
	m = new double* [y];
	for (int i = 0; i < y; i++)
		m[i] = new double[x];
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			m[i][j] = 0;
}
Matrix::Matrix(Matrix& A)
{
	if (this != &A)
	{
		int y_ = A.size_y();
		int x_ = A.size_x();
		double** tmp = new double* [y_];
		for (int i = 0; i < y_; i++)
			tmp[i] = new double[x_];

		for (int i = 0; i < y_; i++)
			for (int j = 0; j <x_; j++)
			{
				(tmp[i][j]) = double(A.m[i][j]);
			}


		this->m = tmp;
		this->x = x_;
		this->y = y_;
			
	}
	else
	{
		m = 0;
		x = 0;
		y = 0;
	}
	c_x = x;
	c_y = y;
}
Matrix::~Matrix()
{
	this;
	for (int i = 0; i < c_y; i++)
		delete[] m[i];
	delete m;
	m = 0;

}
double* Matrix:: operator[] (int a)const
{
	return m[a];
}

Matrix& Matrix::operator=(const Matrix& A)
{

	if (this != &A)
	{
		int y = A.size_y();
		int x = A.size_x();
		double** tmp = new double* [y];
		for (int i = 0; i < y; i++)
			tmp[i] = new double[x];

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				(tmp[i][j]) = (A.m[i][j]);
			}

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = tmp;
		x = x;
		y = y;
		c_x = x;
		c_y = y;

	}
	return *this;
}
Matrix& Matrix::operator=(double** a)
{


		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				(m[i][j]) = (a[i][j]);
			}

		
		x = x;
		y = y;
	
	return *this;
}

Matrix& Matrix::operator+=(Matrix& A)
{
	if (x == A.x and y == A.y)
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				m[i][j] += A.m[i][j];
			}
		}
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix& A) const
{
	Matrix tmp{ y,x };
	if (x == A.x and y == A.y)
	{
		
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				tmp.m[i][j] = m[i][j] + A.m[i][j];
			}
		}
	}
	return tmp;
}

Matrix Matrix::operator*(const Matrix& A) const
{
	Matrix l{ this->y,A.x };
	if (this->x == A.y)
	{
		
		{
			for (int i = 0; i < l.y; i++)
			{
				for (int j = 0; j < l.x; j++)
				{
					double suma = 0;
					for (int k = 0; k < this->x; k++)
					{
						suma += m[i][k] * A[k][j];
					}
					l[i][j] = suma;
				}
			}
		}
		
	}

	return l;
}

Matrix Matrix::operator*(const double a) const
{
	
		Matrix R{ y,x };
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				R.m[i][j] = m[i][j] * a;
			}
		}
		return R;
	
}

Matrix Matrix::operator*=(double a)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			m[i][j] = m[i][j] * a;
		}
	}
	return *this;
}

void Matrix::swap_x(int x1, int x2)
{

	for (int i = 0; i < y; i++)
	{
		std::swap(m[i][x1], m[i][x2]);

	}

}
void Matrix::swap_y(int y1, int y2)
{

	for (int i = 0; i < x; i++)
	{
		std::swap(m[y1][i], m[y1][i]);

	}

}
void Matrix::add_d_y(int d)
{
	if (y + d < c_y)
	{
		y += d;
	}
	else if (this->y + d > 0)
	{
		2 * c_y < y + d ? c_y += 2 * d : c_y *= 2;
		double** tmp = new double* [c_y];
		for (int i = 0; i < c_y; i++)
			tmp[i] = new double[x];

		for (int i = 0; i < y; i++)
			for (int j = 0; j < x; j++)
			{
				tmp[i][j] = this->m[i][j];
			}

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = tmp;
		y = y + d;
	}
	else
	{

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = 0;
		x = y = 0;
	}
}

void Matrix::set_d(int dy,int dx)
{
	if (dy < c_y and dx < c_x)
	{
		y = dy;
		x = dx;
	}
	else
	{
		double** tmp = new double* [dy];
		for (int i = 0; i < dy; i++)
			tmp[i] = new double[dx];

		

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = tmp;
		c_y = y = dy;
		c_x = x = dx;

	}
}

void Matrix::add_d_x(int d)
{

	if (x + d < c_x)
	{
		x += d;
	}
	if (this->x + d > 0)
	{
		2 * c_x < x + d ? c_x += 2 * d : c_x *= 2;
		double** tmp = new double* [y];
		for (int i = 0; i < y; i++)
			tmp[i] = new double[c_x];

		for (int i = 0; i < y ; i++)
			for (int j = 0; j < x && j < c_x ; j++)
			{
				tmp[i][j] = double(this->m[i][j]);
			}

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = tmp;
		x = x + d;
	}
	else
	{

		for (int i = 0; i < y; i++)
			delete[] m[i];
		delete[] m;
		m = 0;
		x = y = 0;
	}
}



const void Matrix::print()
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			std::cout<<std::fixed<<std::setw(7)<<std::setprecision(5) << m[i][j] << " ";

		}
		std::cout << std::endl;
	}
}
const void Matrix::print(int precision,int width)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			std::cout << std::fixed << std::setw(width) << std::setprecision(precision) << m[i][j] << " ";

		}
		std::cout << std::endl;
	}
}
const void Matrix::print(int precision)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			std::cout << std::fixed  << std::setprecision(precision) << m[i][j] << " ";

		}
		std::cout << std::endl;
	}
}
const void Matrix::print_t(int precision)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			std::cout << std::fixed << std::setprecision(precision) << m[j][i] << ", ";

		}
		std::cout << std::endl;
	}
}
const int Matrix::size_y()const
{
	return y;
}

const int Matrix::size_x()const
{
	return x;
}

const int Matrix::capacity_x()const
{
	return c_x;
}

const int Matrix::capacity_y()const
{
	return c_y;
}

Matrix operator*(double a, Matrix A)
{
	Matrix R{ A.y,A.x };
	for (int i = 0; i < A.y; i++)
	{
		for (int j = 0; j < A.x; j++)
		{
			R.m[i][j] = A.m[i][j] * a;
		}
	}
	return R;
}



std::ostream& operator<<(std::ostream& os, Matrix& A)
{
	os << "\n";
	for (int i = 0; i < A.size_y(); i++)
	{
		for (int j = 0; j < A.size_x(); j++)
		{
			os << A[i][j] << " ";

		}
	os<<"\n";
	}
	return os;
}

void gen_dane_wej(Matrix& A, bool zbiezny, int range)
{
	std::default_random_engine generator;
	generator.seed(time(0));
	std::uniform_int_distribution<int> distribution(1, range);
	
	for (int i = 0; i < A.y; i++)
	{
		double suma = 0;
		for (int j = 0; j < A.y; j++)
		{
			 A.m[i][j] = distribution(generator);
			 suma += A.m[i][j];
			
		}
		A.m[i][A.y] = distribution(generator)* distribution(generator);
		if (zbiezny)
		{
			if (A.m[i][i] < suma)
				A.m[i][i] += suma;
		}
	}
}
