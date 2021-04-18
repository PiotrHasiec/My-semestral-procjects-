/** @file */
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <iomanip>
#include "SLE.h"
int main()
{
    using namespace std;
    {
        Matrix a(3, 4);
       
        a[0][0] =5;
        a[0][1] =2;
        a[0][2] = 1;
        a[0][3] = 20;

        a[1][0] = 3;
        a[1][1] = -5;
        a[1][2] = 1;
        a[1][3] = -5;

        a[2][0] = 1;
        a[2][1] = -4;
        a[2][2] = 10;
        a[2][3] = 30;

        Matrix e(4, 5);
        e[0][0] = 1;
        e[0][1] = 2;
        e[0][2] = 3;
        e[0][3] = 1;
        e[0][4] = 4;
       
        e[1][0] = -1;
        e[1][1] = 2;
        e[1][2] = 3;
        e[1][3] = 1;
        e[1][4] = -6;

        e[2][0] = -1;
        e[2][1] = -1;
        e[2][2] = -1;
        e[2][3] = -12;
        e[2][4] = -46;

        e[3][0] = 2;
        e[3][1] = 3.5;
        e[3][2] = 6;
        e[3][3] = 1;
        e[3][4] = 12;

        Matrix f(4, 5);
        f[0][0] = 7;
        f[0][1] = 2;
        f[0][2] = 3;
        f[0][3] = 1;
        f[0][4] = 34;

        f[1][0] = -1;
        f[1][1] = 12;
        f[1][2] = 3;
        f[1][3] = 1;
        f[1][4] = -166;

        f[2][0] = -1;
        f[2][1] = -1;
        f[2][2] = -11;
        f[2][3] = -2;
        f[2][4] = -96;

        f[3][0] = 2;
        f[3][1] = 3.5;
        f[3][2] = 6;
        f[3][3] = 11;
        f[3][4] = 52;
    
        Matrix c(900, 901);
        
     
        Solver* A = new Solver_Seidl;
        Solver* B = new Solver_Gauss;
        Solver* C = new Solver_Residuum;
        Solver* D = new Solver_Jacobi;
        
        constexpr double pr = 0.01;
        ((Solver_i*)A)->set_precision(pr);//A musi byc typu solver_i (dziedziczyc po solver_i) bo inaczej nastapi proba dostepu do skladowej ktora nie istnieje w Solver
        //((Solver_i*)B)->set_precision(0.1); <- dostep do skladowej ktorej solver gauss nie posiada
        ((Solver_i*)C)->set_precision(pr);
        ((Solver_i*)D)->set_precision(pr);

        //układ a
        printf("uklad a\n");
        a.print(0, 5);
        if (A->solv(a))
        {
            cout << "Seidl\n";
            A->results().print(3);
            std::cout << std::endl;
        }

      

       if (C->solv(a))
       {
           cout << "Residuum\n";
           C->results().print(2, 4);
           std::cout << std::endl;
       }
        
       
        if (B->solv(a))
        {
            cout << "Gauss\n";
            B->results().print(3);
            std::cout << std::endl;
        }
    

       if (D->solv(a))
       {
           cout << "Jacobi\n";
           D->results().print(3);
           std::cout << std::endl;
       }
       
      
       //układ e
       printf("uklad e\n");
       e.print(2, 6);

       
       if (A->solv(e))
       {
           cout << "Seidl\n";
           A->results().print(3);
           std::cout << std::endl;
       }

       

       if (C->solv(e))
       {
           cout << "Residuum\n";
           C->results().print(3, 4);
           std::cout << std::endl;
       }
       

       if (B->solv(e))
       {
           cout << "Gauss\n";
           B->results().print(3);
           std::cout << std::endl;
       }
       

       if (D->solv(e))
       {
           cout << "Jacobi\n";
           D->results().print(3);
           std::cout << std::endl;
       }
       

        //ukłd f
       printf("uklad f\n");
       f.print(2,6);

       if (A->solv(f))
       {
           cout << "Seidl\n";
           A->results().print(3);
           std::cout << std::endl;
       }



       if (C->solv(f))
       {
           cout << "Residuum\n";
           C->results().print(3, 4);
           std::cout << std::endl;
       }


       if (B->solv(f))
       {
           cout << "Gauss\n";
           B->results().print(3);
           std::cout << std::endl;
       }


       if (D->solv(f))
       {
           cout << "Jacobi\n";
           D->results().print(3);
           std::cout << std::endl;
       }

       /* a= (a * 2);
        (2*a).print();
        a.print();
        std::cout << std::endl;
        a.add_d_x(3);
        a.add_d_y(20);
        a.set_d(4, 4);
        a[2][3] = 12.000001;
        for (int i =0;i<a.size_x();i++) a[3][i] = i *( i+1);
        std::cout << std::endl;
        std::cout << a[2][3]<<a.size_x()<<a.size_y();
        std::cout << std::endl;
         a = (a * 2);
        (2 * a).print();
        a.print(4);
        a = a * a;
        a.print(4);*/
       gen_dane_wej(c,1,9000);
       printf("uklad c\n");
      // c.print(2, 6);

       if (B->solv(c))
       {
           cout << "Gauss\n";
           B->results().print_t(3);
           std::cout << std::endl;
       }

       if (A->solv(c))
       {
           cout << "Seidl\n";
           A->results().print_t(3);
           std::cout << std::endl;
       }



       if (C->solv(c))
       {
           cout << "Residuum\n";
           C->results().print_t(3);
           std::cout << std::endl;
       }


      
       //Długo się wykonuje

     /*  if (D->solv(c))
       {
           cout << "Jacobi\n";
           D->results().print_t(3);
           std::cout << std::endl;
       }*/
       
       Matrix d(20, 21);
       gen_dane_wej(d, 1, 7000);
       printf("uklad d\n");
       d.print(2, 6);

       if (B->solv(d))
       {
           cout << "Gauss\n";
           B->results().print_t(3);
           std::cout << std::endl;
       }

       if (A->solv(d))
       {
           cout << "Seidl\n";
           A->results().print_t(3);;
           std::cout << std::endl;
       }



       if (C->solv(d))
       {
           cout << "Residuum\n";
           C->results().print_t(3);
           std::cout << std::endl;
       }





       if (D->solv(d))
       {
           cout << "Jacobi\n";
           D->results().print_t(3);
           std::cout << std::endl;
       }
        
      
    
       
        delete A;
        delete B;
        delete C;
        delete D;
    }
   
    _CrtDumpMemoryLeaks();
  
}
 
