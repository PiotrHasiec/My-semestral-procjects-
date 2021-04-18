/** @file */
#pragma once
#include <iostream>
class Matrix///< Dynamic allocated Matrix
{
	double** m;///< pointer on dynamic allocated tabel
	int x;///< size of matrix in x dimension
	int y;///< size of matrix in y dimension
	int c_x;///< capacity of x dimension
	int c_y;///<capacity of y dimension
public:

	/**Konstruktor domyslny macierzy
	Tworzy obiekt ale nie rezerwuje na niego zadnej pamieci*/
	Matrix();

	/** Konstruktor - tworzy macierz o rozmiarach AxB gdzie A to liczba wierszy, a B to liczba kolumn
	@param[in] a liczba wierszy macierzy
	@param[in] b liczba kolumn macierzy*/
	Matrix(int a, int b);

	/** Konstruktor kopiujacy
	@param[in] A macierz za pomoca ktorej nalezy zainicjowac dana macierz*/
	Matrix(Matrix& A);

	/**Destruktor macierzy*/
	~Matrix();

	/**Operator pozwalajacy na dostep do konkretnych komorek macierzy.
	Jesli macierz ma jedna wiersz lub kolumne to nalezy odwolac sie do niej - np A[0][n]
	@param[in] a indekswiersza do ktorego chcemy sie odwolac*/
	double* operator[] (int a) const;

	/**Operator przepisania macierzy
	@param[in] A macierz ktora chcemy przepisac
	@return *this */
	Matrix& operator= (const Matrix& A);

	/**Operator przepisania tablicy do macierzy. Zakladam, ze tablica ma rozmiar taki jak aktualnie ma macierz
	@param[in] a tablica zmiennych typu double, nalezy uwazac na rozmiar tablicy i macierzy
	@return *this */
	Matrix& operator=(double** a);

	/**Operator dodawania macierzy
	@param[in] skladnik sumy
	@return macierz sumy */
	Matrix operator+ (const Matrix& A)const;

	/**Operator dodawania i przypisania macierzy
	@param[in] A skladnik sumy
	@return *this */
	Matrix& operator+= (Matrix& A);

	/**Operator mnozenia macierzy
	@param[in] A prawostronny czynnik iloczynu macierzy 
	@return macierz iloczynu*/
	Matrix operator* (const Matrix& A)const;

	/**Operator mnozenia macierzy przez skalar
	@param[in] a skalar przez ktory ma byc pomnozona macierz
	@return macierz iloczynu*/
	Matrix operator* (const double a)const;

	/**Operator mnozenia macierzy pezez skalar i przypisania
	@param[in] a skalar przez ktory ma byc pomnozona macierz
	@return macierz iloczynu*/
	Matrix operator*= (double a);

	/**Funkcja zaprzyjazniona - operator mnozenia macierzy przez skalar
	@param[in] a skalar przez ktory ma byc pomnozona macierz
	@return macierz iloczynu*/
	friend Matrix operator* (double a,Matrix A);

	/** Zamienia  ze soba kolumny macierzy
	@param[in] x1 indeks kolumny ktora ma byc zamieniona
	@param[in] x2 indeks kolumny ktora ma byc zamieniona*/
	void swap_x(int x1, int x2);

	/** Zamienia  ze soba kolumny macierzy
	@param[in] y1 indeks wiersza ktory ma byc zamieniony
	@param[in] y2 indeks wiersza ktory ma byc zamieniony*/
	void swap_y(int y1, int y2);
	
	/** Dodaje x kolumn do macierzy
	@param[in] x Liczba kolumn ktore chcemy dodac*/
	void add_d_x(int x);

	/**Ustawia rozmiar macierzy na y na x
	@param[in] y Liczba wierszy ktore chcemy posiadac po operacji
	@param[in] x Liczba kolumn ktore chcemy posiadac po operacji*/
	void set_d(int y,int x);

	/** Dodaje y wierszy do macierzy
	@param[in] y Liczba wierszy ktore chcemy dodac*/
	void add_d_y(int y);

	/**Wyswietla macierz*/
	const void print();

	/**Wyswietla macierz
	@param[in] precision ustawia precyzje wyswietlania liczb w macierzy
	@param[in] width ustawia szerokosc wyswietlenia pojedyñczej komorki macierzy*/
	const void print(int precision, int width);

	/**Wyswietla macierz
	@param[in] precision ustawia precyzje wyswietlania liczb w macierzy*/
	const void print(int precision);

	/**Wyswietla macierz transponowan¹
	@param[in] precision ustawia precyzje wyswietlania liczb w macierzy*/
	const void print_t(int precision);

	/**Zaprzyjazniona funkcja operator strumieniowy
	@param[in] os strumieñ do ktorego chcemy przeslac macierz
	@param[in] A Macierz ktora przesylamy do strumienia*/
	friend std::ostream& operator<<(std::ostream& os,  Matrix& A);

	/**Zwraca wartosc y rozmiaru macierzy 
	@return rozmiar y macierzy*/
	const int size_y()const;

	/**Zwraca wartosc x rozmiaru macierzy 
	@return rozmiar x macierzy*/
	const int size_x()const;

	/**Zwraca wartosc x pojemnosci macierzy 
	@return pojemnosc x macierzy*/
	const int capacity_x()const;

	/**Zwraca wartosc y pojemnosci macierzy 
	@return pojemnosc y macierzy*/
	const int capacity_y()const;
	friend void gen_dane_wej(Matrix& A, bool zbiezny,int range);
	

};




