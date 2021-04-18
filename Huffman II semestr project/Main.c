/** @file */
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "sources.h"



int main(int argc, char* argv[])
{
    char oname[40] ="";
    char iname[40] ="";
    int option = 0;
    int return_n = 2;
    readme();
    for (int i = 0; i < argc; i++)//obsˆuga parametr¢w programu
    {

        if (strcmpi(argv[i], "-i") == 0 && i + 1 < argc)
        {
            strncat(iname, argv[++i], 20);
        }
        if (strcmpi(argv[i], "-o") == 0 && i + 1 < argc)
        {
            
            strncat(oname, argv[++i], 20);
        }
        if (strcmpi(argv[i], "-k") == 0 && option != 2 )
        {
            option = 1;
        }
        if (strcmpi(argv[i], "-d") == 0 && option != 1)
        {
            option = 2;
        }
        
    }
    if (option == 1)
         return_n = compress(iname, oname);
    else if (option == 2)
        return_n =  read_file_coded(iname, oname);


    if (return_n == -1)
        printf("Nie udaˆo uzyska† si© dost©pu do conajmniej jednego pliku\nProsz© spr¢bowa† ponownie");
    
   return 0;
}



