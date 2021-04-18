/** @file */

#ifndef FUNKCJE_H
#define FUNKCJE_H
#include <string>


struct link///< Element listy po��cz��/ ga��zie mi�dzy wierzcho�kami
{
	int number; ///< Indeks w�z�a b�d�cego ko�cem tego po��czenia
	link* nextlink; ///<Wska�nik na nast�pny element listy
	char type;///< Typ po��czenia 
	long double value;///<Warto�� wyra�ona w jednostakch zal�znie od typu
	int id; ///< pozwala na identyfikacj� przy odczytywaniu 
	double pr�d;///< Pr�d p�yn�cy przez ga���

};
struct vertex///< Wierzcho�ek grafu/ w�ze� obwodu
{
	int number;///<Nr w�z��
	vertex* nextvertex;///< Wska�nik na nast�pny element listy w�z��w
	link* phead;///< Wska�nik na pierwszy element listy po��cze� wychodz�cych z danego wierzcho�ka
	long double potential;///< Potencja� w�z�a

};

/** Funkcja pobiera z pliku dane i dodaje elementy do listy.
@param[in] name �cie�ka do pliku
@param[in,out] phead Wska�nik na pierwszy element listy
@return true je�li odczyt przebieg� bezb��dnie, false je�i si� nie powi�d�*/
bool download(std::string name, vertex*& phead);

/** Funkcja zapisuje do pliku analiz� obwodu.
@param[in] name �cie�ka do pliku
@param[in] phead Wska�nik na pierwszy element listy
@return true je�li zapis przebieg� bezb��dnie, false je�i si� nie powi�d�*/
bool save(std::string name, vertex* phead);

/** Funkcja rozwi�zuje uk�ad r�wna� liniowych
@param[in,out] Matrix Tablica wsp�czynnik�w uk�adu r�wnana� linowych w postaci [n][n+1], rozwi�zania zwaracane s� w ostatniej kolumnie uk�adu r�wna�.
@param[in] n Liczba zmiennych w uk�adzie
@return true gdy uk�ad jest rozwi�zywalny, false je�li uk�ad jest sprzeczny lub to�samo�ciowy
*/
bool gauss(long double**& Matrix, int n);

/** Funkcja sprawdza liczb� element�w w liscie - wierzcho�k�w w grafie.
@param[in] phead Wska�nik na pierwszy element listy
@return liczba element�w w li�cie
*/
int count(vertex* phead);

/** Funkcja tworzy, na podstawie grafu, macierz konduktancji  oraz wymusze� pr�dowych.
@param[in] phead Wska�nik na pierwszy element listy
@return Wska�nik na dwuwymiarow� tablic�
*/
long double** makematrix(vertex* phead);

/** Funkcja oblicza sum� konduktancji miedzy dwoma zadanymi w�z�ami, lub sum� konduktancji pod��czonych do danego w�z�a.
@param[in] first Indeksy w�z��w miedzy kt�rymi ma by� policzona suma konduktancji
@param[in] second Indeksy w�z��w miedzy kt�rymi ma by� policzona suma konduktancji
@param[in] phead Wska�nik na pocz�tek listy
*/
long double sumuj_przewodno�ci_pomi�dzy_danymi_w�za�mi(int first, int second, vertex* phead);

/** Funkcja oblicza pr�dy p�yn�ce przez wszystkie po��cznie miedzy wierzcho�kami grafu zadekalrowanymi w li�ciee
@param[in] phead Wska�nik na pocz�tek listy
*/
void generuj_pr�dy_w_ga��ziach(vertex* phead);

/** Funkcja usuwa list�
@param[in,out] phead Wska�nik na pocz�tek listy, po usuni�ciu listy zwracany jest nullptr
*/
void delete_vertices_forend_r(vertex*& phead);

/**Funkcja sortuje graf
@param[in, out] phead Wska�nik na pocz�tek listy
*/
void sort(vertex* a);

#endif