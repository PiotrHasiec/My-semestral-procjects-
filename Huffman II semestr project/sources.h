/** @file */
#pragma once

typedef struct node ///< struktura węzła drzewa
{
    unsigned int frequency;///< częstość występowania bitu
    int bajt;///< bit którego dotyczy powyższa częstość lub -1 jeśli w węźle nie znajduje się żaden 
    struct node* left_n; ///< wskaźnik na lewego potomka
    struct node* right_n;///< wskaźnik na prawego potomka

} node;

typedef struct min_heap ///< Struktura kopca (statycznego)/ Kolejka priorytetowa typu min
{
    node* tab[256];///< tablica przechowująca wierzchołki drzewa
    int lengh;///< długość aktualnej kolejki
} min_heap;

/** Funkcja usuwa drzewo bez liści
@param[in,out] root Wskaźnik na korzeń drzewa */
void delete_tree(node* root);

/** Funkcja przywraca własności kopca typu min
@param[in,out] A Wskaźnik na kolejkę
@param[in] i element tablicy dla którego wywołujemy funkcję*/
void min_heapify(min_heap* A, int i);

/** Funkcja wstawia klucz do kopca
@param[in,out] A Wskaźnik na kolejkę
@param[in] key Klucz który należy wstawić do kolejki*/
void heap_insert(min_heap* A, node* key);

/**Buduje kopiec typu min z podanej  elementowej tablicy
@param[in,out] A Wskaźnik na kolejkę
@param[in] n ilość elementów tablicy
@return zwraca kolejkę typu min*/
min_heap build_min_heap(node* A, int n);

/**Buduje kopiec typu min z podanej  elementowej tablicy
@param[in,out] A Wskaźnik na kolejkę
@param[in] n ilość elementów tablicy
@return zwraca kolejkę typu min* zwraca kolejkę typu min*/
min_heap build_min_heap_i(node* A, int n);

/**Zciąga z kopca element o najmniejszej częstości występowania
@param[in,out] A Wskaźnik na kolejkę
@return zwraca element o najmniejszej częstości występowania*/
node* extract_min(min_heap* A);

/**Buduje drzewo kodów Huffmna
@param[in,out] leafs Tablica 256 liści drzewa
@return Wskaźnik na korzeń drzewa*/
node* add_to_tree(node* leafs);

/**Funkcja uzupełnia dane w tablicy liści dotyczące częstości występowania bajtów na podsawie pliku
@param[in,out] tab Tablica 256 liści drzewa
@param[in] nazwa Nazwa pliku dla którego należy zrobić statystykę
@return Wskaźnik na przyjętą tablicę*/
node* read_file_uncoded(char* nazwa, node* tab);

/**Funkcja tworzy słownik w którym dla i-tego wiersza występuje kod bajtu o wartości i, kod jest ciągiem 0 i 1 zakończonym liczbą 2
@param[in] A Wskaźnik na korzeń drzewa modów Huffmana
@param[in,out] code Tablica 257x256 w której zwracany będzie słownik
@param[in] i Zmienna pomocnicza, domyślnie 0 */
void codematrix(node* A, int** code, int i);

/**Pomocnicza funkcja zamiany liczb na ciąg znaków 0 i 1 zakończony 2 jako znakiem końca ciągu
@param[in] number Liczba którą należy zmienić
@param[in,out] string_n Zwracany ciąg
@param[in,out] w Pierwszy niezapisany element ciągu*/
void number_to_string(char number, char* string_n, int* w);

/**Funkcja tworzy plik readme*/
void readme();

/**Funkcja tworzy obsługująca funkcjonalność kompresji pliku
@param[in] iname Nazwa pliku wejściowego (niezakodowanego)
@param[in] oname Nazwa pliku wyjściowego */
int compress(char* iname, char* oname);

/**Funkcja tworzy zakodowany plik razem z danymi potrzebnymi do jego odczytu
@param[in] iname Nazwa pliku wejściowego (niezakodowanego)
@param[in] oname Nazwa pliku wyjściowego
@param[in] codevector słownik kodów Huffmana
@param[in] leafs_huffman_tree Tablica liści drzewa huffmana 
@return 0 w przypadku poprawnego wykonania funkcji*/
int save_to_file(char* iname, char* oname, int** codevector, node* leafs_huffman_tree);

/**Funkcja tworzy obsługująca funkcjonalność dekompresji pliku
@param[in] iname Nazwa pliku wejściowego (niezakodowanego)
@param[in] oname Nazwa pliku wyjściowego 
@return 0 w przypadku poprawnego wykonania funkcji*/
int read_file_coded(char* iname, char* oname);
