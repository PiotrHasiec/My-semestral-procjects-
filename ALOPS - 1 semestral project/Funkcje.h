/** @file */

#ifndef FUNKCJE_H
#define FUNKCJE_H
#include <string>


struct link///< Element listy po³¹czêñ/ ga³êzie miêdzy wierzcho³kami
{
	int number; ///< Indeks wêz³a bêd¹cego koñcem tego po³¹czenia
	link* nextlink; ///<WskaŸnik na nastêpny element listy
	char type;///< Typ po³¹czenia 
	long double value;///<Wartoœæ wyra¿ona w jednostakch zalêznie od typu
	int id; ///< pozwala na identyfikacjê przy odczytywaniu 
	double pr¹d;///< Pr¹d p³yn¹cy przez ga³¹Ÿ

};
struct vertex///< Wierzcho³ek grafu/ wêze³ obwodu
{
	int number;///<Nr wêz³¹
	vertex* nextvertex;///< WskaŸnik na nastêpny element listy wêz³ów
	link* phead;///< WskaŸnik na pierwszy element listy po³¹czeñ wychodz¹cych z danego wierzcho³ka
	long double potential;///< Potencja³ wêz³a

};

/** Funkcja pobiera z pliku dane i dodaje elementy do listy.
@param[in] name Œcie¿ka do pliku
@param[in,out] phead WskaŸnik na pierwszy element listy
@return true jeœli odczyt przebieg³ bezb³êdnie, false jeœi siê nie powiód³*/
bool download(std::string name, vertex*& phead);

/** Funkcja zapisuje do pliku analizê obwodu.
@param[in] name Œcie¿ka do pliku
@param[in] phead WskaŸnik na pierwszy element listy
@return true jeœli zapis przebieg³ bezb³êdnie, false jeœi siê nie powiód³*/
bool save(std::string name, vertex* phead);

/** Funkcja rozwi¹zuje uk³ad równañ liniowych
@param[in,out] Matrix Tablica wspó³czynników uk³adu równanañ linowych w postaci [n][n+1], rozwi¹zania zwaracane s¹ w ostatniej kolumnie uk³adu równañ.
@param[in] n Liczba zmiennych w uk³adzie
@return true gdy uk³ad jest rozwi¹zywalny, false jeœli uk³ad jest sprzeczny lub to¿samoœciowy
*/
bool gauss(long double**& Matrix, int n);

/** Funkcja sprawdza liczbê elementów w liscie - wierzcho³ków w grafie.
@param[in] phead WskaŸnik na pierwszy element listy
@return liczba elementów w liœcie
*/
int count(vertex* phead);

/** Funkcja tworzy, na podstawie grafu, macierz konduktancji  oraz wymuszeñ pr¹dowych.
@param[in] phead WskaŸnik na pierwszy element listy
@return WskaŸnik na dwuwymiarow¹ tablicê
*/
long double** makematrix(vertex* phead);

/** Funkcja oblicza sumê konduktancji miedzy dwoma zadanymi wêz³ami, lub sumê konduktancji pod³¹czonych do danego wêz³a.
@param[in] first Indeksy wêz³ów miedzy którymi ma byæ policzona suma konduktancji
@param[in] second Indeksy wêz³ów miedzy którymi ma byæ policzona suma konduktancji
@param[in] phead WskaŸnik na pocz¹tek listy
*/
long double sumuj_przewodnoœci_pomiêdzy_danymi_wêza³mi(int first, int second, vertex* phead);

/** Funkcja oblicza pr¹dy p³yn¹ce przez wszystkie po³¹cznie miedzy wierzcho³kami grafu zadekalrowanymi w liœciee
@param[in] phead WskaŸnik na pocz¹tek listy
*/
void generuj_pr¹dy_w_ga³êziach(vertex* phead);

/** Funkcja usuwa listê
@param[in,out] phead WskaŸnik na pocz¹tek listy, po usuniêciu listy zwracany jest nullptr
*/
void delete_vertices_forend_r(vertex*& phead);

/**Funkcja sortuje graf
@param[in, out] phead WskaŸnik na pocz¹tek listy
*/
void sort(vertex* a);

#endif