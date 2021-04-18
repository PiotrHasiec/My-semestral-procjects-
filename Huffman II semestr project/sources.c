/** @file */
#pragma once


#include <stdlib.h>
#include <stdio.h>
#include "sources.h"



void delete_tree(node* root)
{
    if (root)
    {
        delete_tree(root->left_n);
        delete_tree(root->right_n);
        if (root->left_n || root->right_n)
            free(root);
    }
}

void min_heapify(min_heap* A, int i)
{
    int smallest;
    int l = (i * 2);
    int r = (l + 1);
    if (l < (*A).lengh && (*A).tab[l]->frequency < (*A).tab[i]->frequency)
        smallest = l;
    else
        smallest = i;
    if (r < (*A).lengh && (*A).tab[r]->frequency < (*A).tab[smallest]->frequency)
        smallest = r;
    if (smallest != i)
    {
        node* tempi = A->tab[i];
        A->tab[i] = A->tab[smallest];
        A->tab[smallest] = tempi;
        min_heapify(A, smallest);

    }
}
void heap_insert(min_heap* A, node* key)
{
    (*A).lengh += 1;
    A->tab[(A->lengh) - 1] = key;
    for (int i = (A->lengh) - 1; (i >= 0 && A->tab[i / 2]->frequency > A->tab[i]->frequency); i = (i / 2))
    {
        node* tmp = A->tab[i];
        A->tab[i] = A->tab[i / 2];
        A->tab[i / 2] = tmp;

    }

}
min_heap build_min_heap(node* A, int n)
{
    min_heap ret;
    ret.lengh = n;

    for (int i = 0; i < n; i++)
    {
        ret.tab[i] = (A + i);
        ret.tab[i]->left_n = 0;
        ret.tab[i]->right_n = 0;
    }
    for (int i = (n / 2); i >= 0; i--)
    {
        min_heapify(&ret, i);
    }
    return ret;
}

min_heap build_min_heap_i(node* A, int n)
{
    min_heap ret;
    ret.lengh = 1;
    ret.tab[0] = A;
    for (int i = 1; i < n; i++)
    {
        heap_insert(&ret, &A[i]);
    }
    return ret;
}

node* extract_min(min_heap* A)
{
    node* a = NULL;
    if (A->lengh > 0)
    {
        a = (A->tab[0]);
        A->tab[0] = A->tab[(A->lengh - 1)];
        A->lengh -= 1;
        min_heapify(A, 0);

    }
    return a;
}

node* add_to_tree(node* leafs)
{
    min_heap kolejka = build_min_heap(leafs, 256);
    for (int i = 0; i < 255; i++)
    {
        node* tmp = malloc(sizeof( node));
        tmp->left_n = extract_min(&kolejka);
        tmp->right_n = extract_min(&kolejka);
        tmp->frequency = (tmp->left_n->frequency + tmp->right_n->frequency);
        tmp->bajt = -1;
        heap_insert(&kolejka, tmp);
    }
    return extract_min(&kolejka);
}
node* read_file_uncoded(char* nazwa, node* tab)
{
    FILE* pfile;
    pfile = fopen(nazwa, "rb");
    for (int i = 0; i < 256; i++)
    {
        tab[i].bajt = i;
        tab[i].frequency = 0;
        tab[i].left_n = 0;
        tab[i].right_n = 0;

    }
   
    if (pfile)
    {
        unsigned int bufor = 0;
        while (fread(&bufor, sizeof(char), 1, pfile))
        {
           
            tab[bufor].frequency++;
        }
        fclose(pfile);
    }
    
    return tab;
}
void codematrix(node* A, int** code, int i)/// zwraca tablice(słownik) kodów huffmana na podstawie drzewa huffmna
{

    if (A)
    {


        if (A->left_n)
        {

            code[256][i] = 0;
            (i)++;
            codematrix(A->left_n, code, i);
            code[256][i] = 2;
            (i)--;
        }

        if (A->right_n)
        {

            code[256][i] = 1;
            (i)++;
            codematrix(A->right_n, code, i);
            code[256][i] = 2;
            (i)--;
        }

        if ((!A->left_n) && (!A->right_n))
        {

            for (int k = 0; k < 256; k++)
            {
                if (A->bajt >= 0)
                {

                    if (code[256][k] < 2)
                        code[A->bajt][k] = code[256][k];
                    else
                        break;
                }
            }

        }

    }


}
int save_to_file(char* iname, char* oname, int** codevector, node* leafs_huffman_tree)
{
   
    FILE* pfile;
    FILE* pwritefile;
    pfile = fopen(iname, "rb");
    pwritefile = fopen(oname, "wb");
    if (pfile && pwritefile)
    {
        for (int i = 0; i < 256; i++)
        {
            fwrite(&(leafs_huffman_tree[i].frequency), sizeof(unsigned int), 1, pwritefile);
        }
        //fwrite(leafs_huffman_tree, sizeof(node), 256, pwritefile);
        unsigned int read_bufor = 0;
        char write_bufor[300];
        for (int i = 0; i < 300; i++)
        {
            write_bufor[i] = 2;
        }
        int wskaz_konca = 0;//pierwsze wolne miejsze w buforze zapisu i zarazem liczba bitów w buforze
        while (fread(&read_bufor, sizeof(char), 1, pfile))//dopóki uda się odczytać z pliku
        {
         
            for (int i = 0; codevector[read_bufor][i] < 2; i++)//przepisz do bufora kod pobranego bitu
            {
                write_bufor[wskaz_konca] = codevector[read_bufor][i];
                wskaz_konca++;
            }


            int i = 0;
            for (; i < 8 * ((wskaz_konca) / 8);)//dopóki 'i' nie osiągnie liczby pełnych bajtów w pliku
            {
                char write = 0;
                for (int j = 0; j < 8; j++)//dopóki nie złożysz z kodu całego bajtu do zapisania
                {
                    write = write * 2 + write_bufor[i];
                    i++;
                }
                fwrite(&write, 1, 1, pwritefile); 

            }

            int j = 0;
            for (; i < wskaz_konca; i++)
            {
                write_bufor[j] = write_bufor[i];
                j++;
            } 
            for (int k = j; k < wskaz_konca; k++)
            {
                write_bufor[k] = 2;
            }
            wskaz_konca = j;
            
            

        }
        char write = 0;

        {
            for (int k = 0; k < 8; k++)
            {
                if (write_bufor[k] < 2)
                {
                    write = 2 * write + write_bufor[k];
                   
                }

            }
            fwrite(&write, 1, 1, pwritefile); 
            write = (char)(wskaz_konca);
            fwrite(&write, 1, 1, pwritefile);
        }
        fclose(pfile);
        fclose(pwritefile);
        return 0;
    }

    return 1;
}
void number_to_string(char number, char* string_n, int* w)
{
    
    for (int i = 7;  i >= 0 ;i-- )
    {
        if(number % 2)
            string_n[*w + i] ='1';
        else
            string_n[*w + i] = '0';
        number = number >> 1;
    }
    *w += 8;
    string_n[*w ] = 2;
}
int find_eqivalent(node* root, char* code,int* w)
{
    int i = 0;
    int k = 0;
    int returnn = 300;//korzeń nie istnieje
    node* tmp_root = root;
    if (tmp_root)
    {
        while (tmp_root->left_n || tmp_root->right_n)
        {
            
            if (code[i] == '0')
                tmp_root = tmp_root->left_n;
            else if (code[i] == '1')
                tmp_root = tmp_root->right_n;
            else
                return 301;// należy przesłać do funkcji dłuższy fragment pliku
            i++;
        }
        returnn = tmp_root->bajt;
       
        int j = 0;
        for (; code[j - 1] != 2; j++)
        {
            code[j] = code[i];
            i++;
            *w = j;
        }
        *w--;
        code[j] = 2;
        code[j+1] = 2;
    }
    return returnn;
}
int read_file_coded(char* iname, char* oname)
{

    FILE* pfile; pfile = fopen(iname, "rb");
    FILE* pwritefile; pwritefile = fopen(oname, "wb");
    node leafs_huffman_tree[256] ;
    node* root = 0;
    char r_buffor[3] ;
    int w_buffor = 0;
    char string_n[300];
    for (int i = 0; i < 300; i++)
    {
        string_n[i] = 2;
    }
    int w = 0;



    if (pfile && pwritefile)
    {
        for (int i = 0; i < 256; i++)
        {
            fread(&(leafs_huffman_tree[i].frequency), sizeof(unsigned int), 1, pfile);//pobiera tablicę częstości występowania bajtów
            leafs_huffman_tree[i].bajt = i;
        }


        root = add_to_tree(leafs_huffman_tree);//tworzy drzewo kodów huffmana
        fread(r_buffor, sizeof(char), 2, pfile);//wczytuje 2 pierwsze bajty
        while (fread((&r_buffor[2]), sizeof(char), 1, pfile))//dopóki uda się wczytać z pliku bajt
        {

            number_to_string(r_buffor[0], string_n, &w);//pierwszy bajt w buforze zamienia na ciąg zer i jedynek
            if (w > 125)//jeśli wskaźnik końca ciągu jest większy niż 125
                for (;w;)//to dopóki się nie wyzeruje
                {

                    w_buffor = find_eqivalent(root, string_n, &w);//znajdź bajt odpowiadający kodowi znajdującemu się w ciągu string_n

                    if (w_buffor < 257)//a jeśli funkcja nie zwróciła wartość oznaczającą że niema pełnego słowa kodowego w ciągu
                    {
                        fwrite(&w_buffor, 1, 1, pwritefile);//zapisz bajt do pliku wynikowego
                    }
                    else
                    {

                        break;// wyjdź z pętli
                    }
                }
            r_buffor[0] = r_buffor[1];//przesuwanie bajtów w buforze 
            r_buffor[1] = r_buffor[2];
        }


        w_buffor = find_eqivalent(root, string_n, &w);//jeśli nie udało się wczytać bajtu z pliku to opróżniam bufor

        while (w_buffor < 257)
        {
            fwrite(&w_buffor, 1, 1, pwritefile);
            w_buffor = find_eqivalent(root, string_n, &w);
        }




        for (int i = r_buffor[1] - 1; i >= 0 && w < 256; i--)//przpisuję przedostatni bajt z uwzględnieniem ostatniego bajtu (szczegóły w sprawozdaniu)
        {
            if (r_buffor[0] % 2)
                string_n[w + i] = '1';
            else
                string_n[w + i] = '0';
            r_buffor[0] = r_buffor[0] >> 1;

        }
        w += r_buffor[1];
        w_buffor = find_eqivalent(root, string_n, &w);
        while (w_buffor < 257)//opróżniam bufor
        {
            fwrite(&w_buffor, 1, 1, pwritefile);
            w_buffor = find_eqivalent(root, string_n, &w);
        }


        fclose(pfile);
        fclose(pwritefile);
        delete_tree(root);
        return 0;
    }
    return -1;
}
int compress(char* iname, char* oname)
{
    node leafs_huffman_tree[256];
    node* root = 0;
    int return_n = 0;

    int** codevector = (int**)calloc(257, sizeof(int*));
    for (int i = 0; i < 257; i++)
    {
        codevector[i] = (int*)calloc(256, sizeof(int));
        for (int j = 0; j < 256; j++)
        {
            codevector[i][j] = 2;
        }
    }

    read_file_uncoded(iname, leafs_huffman_tree);
    root = add_to_tree(leafs_huffman_tree);
    codematrix(root, codevector, 0);
    return_n = save_to_file(iname, oname, codevector, leafs_huffman_tree);

    for (int i = 0; i < 257; i++)
    {
        free(codevector[i]);
    }
    free(codevector);
    delete_tree(root);
    root = 0;
    return return_n;
}

void readme()
{
    FILE* pfile; pfile = fopen("readme.txt", "w");
    fprintf(pfile, "Program Huffman3.exe uruchamiany jest z konsoli systemu z odpowiednimi przełącznikami:\n");
    fprintf(pfile, "-k lub -d - kolejno tryb kompresji lub rozpakowywania pliku\n");
    fprintf(pfile, "-i - plik wejściowy dla programu\n-o - plik wyjściowy dla programu\n");
    fprintf(pfile, "Nazwy plików należy podawać w formacie NAZWA.ROZSZERZENIE również przy dekompresji pliku\n");
    fclose(pfile);
}
