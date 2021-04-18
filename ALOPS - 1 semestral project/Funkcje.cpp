/** @file */

#include <iostream>
#include <string>
#include <clocale>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "Funkcje.h"
using namespace std;

const long double op�r_wewn�trzny = 0.0000001;

int count(vertex* phead)
{
	int count = 0;
	while (phead)
	{
		phead = phead->nextvertex;
		count++;
	}
	return count;
}


bool gauss(long double**& Matrix, int n)
{
	int i, j, k;
	long double m;
	n -= 1;
	for (i = 1; i < n; i++)//Sprowadzenie do macierzy tr�jk�tnej
	{
		for (j = i; j < n; j++)
		{
			if (Matrix[i - 1][i - 1] == 0) return false;
			m = -Matrix[j][i - 1] / Matrix[i - 1][i - 1];
			for (k = i - 1; k < n + 1; k++)
				Matrix[j][k] += m * Matrix[i - 1][k];
		}
	}
	for (int i = n - 1; i >= 0; i--)//Wylicznie kolejnych potencja��w
	{

		for (int j = n - 1; j >= 0; j--)
		{
			if (j != i)
				Matrix[i][n] -= Matrix[i][j] * Matrix[j][n];
		}
		if (Matrix[i][i] == 0)
		{
			cerr << "Zadeklarowano sprzeczny lub niesp�jny graf obwodu" << endl;
			return 0;
		}
		Matrix[i][n] = (Matrix[i][n]) / Matrix[i][i];
	}
	return true;
}

void delete_links_forend_r(link*& phead)
{
	link* phead1;
	while (phead)
	{
		phead1 = phead;
		delete phead;
		phead = phead1;
		
	}
	phead = nullptr;
}


void delete_vertices_forend_r(vertex*& phead)
{
	vertex* phead1;
	while (phead)
	{
		phead1 = phead->nextvertex;
		delete phead;
		phead = phead1;

	}
	phead = nullptr;
}


void add_l(vertex*& p, int begin, int end, char t, long double  v, int i)
{
	if (begin == end) return;
	vertex* pointer = p;
	if (not p)//Je�eli graf nie istnieje, sprawiamy, �e istnieje 
	{
		p = new vertex{ begin,nullptr,new link{ end ,nullptr,t,v,i } };
		if (t != 'R')
			p->nextvertex = new vertex{ end,nullptr,new link{ begin ,nullptr ,t,-v,i} };//dodajemy nowy wierzcho�ek o numerze ko�ca z po��czeniem do wierzcho�ka pocz�tkowego
		else
			p->nextvertex = new vertex{ end,nullptr,new link{ begin ,nullptr ,t,v,i} };
	}
	else
	{
		while (pointer->nextvertex && pointer->number != begin)//szukamy pocz�tku po��czenia kt�re chcemy doda� lub je�li go nie ma - ostatniego wierzcho�kaw grafie
			pointer = pointer->nextvertex;
		if (pointer->number == begin)//je�li znale�li�my
			pointer->phead = new link{ end ,pointer->phead,t,v,i };//dodajemy po��czenie
		else
			pointer->nextvertex = new vertex{ begin,nullptr,new link{ end ,nullptr,t,v ,i} };//dodajemy nowy wierzcho�ek o numerze ko�ca z po��czeniem do wierzcho�ka pocz�tkowego

		pointer = p;

		while (pointer->nextvertex && pointer->number != end)//szukamy wierzcho�ka ko�cowego dla tego po��czenia
			pointer = pointer->nextvertex;

		if (pointer->number == end)//je�li znale�li�my
			if (t != 'R')
				pointer->phead = new link{ begin ,pointer->phead ,t,-v ,i};//dodajemy po��czenie
			else
				pointer->phead = new link{ begin ,pointer->phead ,t,v ,i};//dodajemy po��czenie
		else
			if (t != 'R')
				pointer->nextvertex = new vertex{ end,nullptr,new link{ begin ,nullptr ,t,-v,i} };//dodajemy nonwy wierzcho�ek o numerze ko�ca z po��czeniem do wierzcho�ka pocz�tkowego
			else
				pointer->nextvertex = new vertex{ end,nullptr,new link{ begin ,nullptr ,t,v,i} };
	}

}

bool download(string name, vertex*& a)
{
	string linia;
	ifstream plik(name);
	int begin;
	int end;
	char type;
	long double value;
	int i = 0;
	if (plik)
		while (plik >> type >> begin >> end >> value)//Dop�ki wczytanie danych z pliku przebieg�o pomy�lnie 
		{
			i++;
			switch (type)
			{
			case 'r': type = 'R'; break;
			case 'e': type = 'E'; break;
			case 'i': type = 'I'; break;
			}
		
			if (type == 'R' && value <= 0)
			{
				cout << "B��dne dane" << endl;
				plik.close();
				return false;
			}

			if (type == 'R' or type == 'I' or type == 'E')
			{				
				add_l(a, begin, end, type, value,i);
			}
			else
			{
				cout << "B��dna warto�� typu" << endl;
				plik.close();
				return false;
				break;
			}
		}

	else
	{
		cout << "Wyst�pi� b��d odczytu." << endl << "Sprawd� poprawno�� podanej �cie�ki do pliku" << endl;
		return false;
	}
	if (plik.bad() || (plik.fail() && not plik.eof()))
	{
		cout << "Wyst�pi� b��d odczytu." << endl << "Prawdopodaobnie podane zosta�y nieprawid�owe dane"<<endl;
		plik.close();
		return false;
	}
	plik.close();
	return true;

}


long double sumuj_wymuszenia_pr�dowe(int nr, vertex* phead)
{
	long double  e = 0;

	link* branch;

	while (phead && nr)
	{
		nr--;
		phead = phead->nextvertex;
	}

	if (phead)
	{
		branch = phead->phead;

		while (branch)
		{
			if (branch->type == 'I')
				e -= branch->value;

			if (branch->type == 'E')
			{
				e -= (branch->value) / (op�r_wewn�trzny);
			}
			branch = branch->nextlink;
		}
	}
	return e;
}


long double sumuj_przewodno�ci_pomi�dzy_danymi_w�za�mi(int first, int second, vertex* Phead)
{
	long double sum = 0;
	vertex* phead = Phead;
	if (first != second and phead)//przypadek dla g��wnej przek�tnej
	{
	
		while (phead && second)
		{
			second--;
			phead = phead->nextvertex;
		}

		if (not phead) return 0;

		second = phead->number;
		phead = Phead;

		while (phead && first)
		{
			first--;
			phead = phead->nextvertex;
		}
		if (phead)
		{
			link* branch = phead->phead;
			while (branch)
			{
				if (branch->type == 'R' && branch->number == second)
					sum -= 1 / (branch->value);
				if (branch->type == 'E' && branch->number == second)
					sum -= 1 / op�r_wewn�trzny;
				branch = branch->nextlink;
			}
		}
	}
	return sum;
}
long double sumuj_wszystkie_przewodno�ci_pod��czone_do_w�z�a(int i, vertex* phead)
{
	long double sum = 0;

	while (phead && i)
	{
		i--;
		phead = phead->nextvertex;
	}
	if (phead)
	{
		link* branch = phead->phead;

		while (branch)
		{
			if (branch->type == 'R')
				sum += 1 / (branch->value);

			if (branch->type == 'E')
				sum += 1 / op�r_wewn�trzny;

			branch = branch->nextlink;

		}

	}
	return sum;
}

long double** makematrix(vertex* phead)
{
	vertex* a = phead;
	long double** matrix;
	int n = count(phead);

	if (n == 0) 
	{
		cout << "B��d"<<endl<<"Podany plik jest pusty" << endl;
		return nullptr;
	}

	matrix = new long double* [n - 1];//twprzenie dynamicznej tablicy

	for (int i = 0; i < (n - 1); i++)
		matrix[i] = new long double[n] {};

	for (int i = 0; i < (n - 1); i++)//przypadek dla wyszytkich p�l opr�cz przek�tnej g��wnej
	{
		for (int k = 0; k < (n - 1); k++)
			matrix[i][k] = sumuj_przewodno�ci_pomi�dzy_danymi_w�za�mi(i, k, phead);
	}


	for (int i = 0; i < (n - 1); i++)//przypadek dla przek�tnej g��wnej
	{
			matrix[i][i] = sumuj_wszystkie_przewodno�ci_pod��czone_do_w�z�a(i, phead);
	}


	for (int i = 0; i < (n - 1); i++)
	{
		matrix[i][n - 1] = sumuj_wymuszenia_pr�dowe(i, phead);
	}


	return matrix;



}


void generuj_pr�dy_w_ga��ziach(vertex* Phead)
{
	link* pol;
	auto statphead = Phead;
	while (Phead)
	{
		pol = Phead->phead;
		while (pol)
		{
			if (pol->type == 'I')
				pol->pr�d = pol->value;//�r�d�a pr�dowe wymuszaj� pr�d o zadaniej warto�ci


			vertex* tmpPhead = statphead;
			if (pol->type == 'R')
			{
				int end = pol->number;
				while (tmpPhead && (tmpPhead->number != end))//szukanie wierzcho�k ko�cowego by m�c policzy� r�nic� potencja��w
					tmpPhead = tmpPhead->nextvertex;

				if (tmpPhead)
					pol->pr�d = (1 / (pol->value)) * (Phead->potential - tmpPhead->potential);// I = U/R
			}
			if (pol->type == 'E')
			{
				int end = pol->number;
				while (tmpPhead && (tmpPhead->number != end))//szukanie wierzcho�ka ko�cowego by m�c policzy� r�nic� potencja��w
					tmpPhead = tmpPhead->nextvertex;

				if (tmpPhead)
					pol->pr�d = (1 / (op�r_wewn�trzny)) * (Phead->potential - tmpPhead->potential + pol->value);// I = U/R

			}

			pol = pol->nextlink;
		}

		Phead = Phead->nextvertex;
	}
}
bool is_readed(int nr, vector<int> id)
{
	for (int i = 0; i < id.size(); i++)
	{
		if (id[i] == nr) return 1;

	}
	return 0;
}

bool save(string name, vertex* phead)
{
	auto statphead = phead;
	ofstream plik(name);
	double moc = 0;
	vector <int> id;

	if (plik)
	{
		
		
		plik << setw(3) << "Typ" << setw(4) << "W1" << setw(6) << "W2" << setw(11) << "Warto��" << setw(11) << "Pr�d" << setw(16) << "Napi�cie" << setw(11) << "Moc" << endl;

		plik << endl;
		
		while (phead)
		{
			
			link* pol = phead->phead;
			
			while (pol)
			{
				if (not is_readed(pol->id, id))
				{
					id.push_back(pol->id);
					vertex* sphead = statphead;


					plik << fixed << setprecision(2);
					switch (pol->type)
					{
					case 'R':
						moc += ((pol->pr�d) * (pol->pr�d) * (pol->value));
						plik << pol->type << " " << setw(4) << phead->number << " " << setw(5) << pol->number << " " << setw(8) << pol->value << " OM" << setw(6) << " I = " << setw(6) << pol->pr�d << "A" << setw(6) << " U = " << setw(9) << (pol->pr�d) * (pol->value) << "V" << setw(6) << " P = " << setw(7) << ((pol->pr�d) * (pol->pr�d) * (pol->value)) << "W" << endl;
						break;

					case 'E':
						moc += (-(pol->pr�d) * (pol->value));
						plik << pol->type << " " << setw(4) << phead->number << " " << setw(5) << pol->number << " " << setw(8) << pol->value << setw(3) << "V" << setw(6) << " I = " << setw(6) << pol->pr�d << "A" << setw(6) << " U = " << setw(9) << (pol->value) << "V" << setw(6) << " P = " << setw(7) << (-(pol->pr�d) * (pol->value)) << "W" << endl;
						break;

					case 'I':
						double u = phead->potential;

						while (sphead and sphead->number != pol->number)
						{
							sphead = sphead->nextvertex;
						}

						u -= sphead->potential;

						plik << pol->type << " " << setw(4) << phead->number << " " << setw(5) << pol->number << " " << setw(8) << pol->value << setw(3) << "A" << setw(6) << " I = " << setw(6) << pol->pr�d << "A" << setw(6) << " U = " << setw(9) << u << "V" << setw(6) << " P = " << setw(7) << (u * pol->pr�d) << "W" << endl;
						moc += (u * pol->pr�d);

						break;

					}
				}

				pol = pol->nextlink;
			}
			phead = phead->nextvertex;
		}
		plik << endl;
		plik << "Suma mocy:" << setw(56) <<abs( moc) << "W" << endl;
		plik << endl << "Typ:" << endl << "I - �r�d�o pr�dowe R - Opornik E - �r�d�o napi�ciowe" << endl;
		plik.close();
		cout << "Poprawnie zapisano dane do pliku" << endl;
		return true;
	}
	cout << "B��d zapisu" << endl;
	return false;

}

void swapp(vertex* phead1, vertex* phead2 )
{

	swap(phead1->number, phead2->number);
	swap(phead1->phead, phead2-> phead);
	swap(phead1->potential, phead2->potential);

}

void sort(vertex* Phead0)
{
	vertex* phead1 = Phead0;
	vertex* phead;
	while (Phead0)
	{
		phead = phead1;
		while (phead && phead->nextvertex)
		{
			if ((phead->number) > (phead->nextvertex->number))
				swapp(phead, phead->nextvertex);
			phead = phead->nextvertex;
		}

		Phead0 = Phead0->nextvertex;
	}
}



