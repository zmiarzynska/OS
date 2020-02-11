#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "procinfo.h"

int main(int argc,char* argv[])
{
       procinfo(argv[0]);
       
       if(argc!=3)
         {
           printf("Zla liczba argumentow. Prawidlowa liczba argumentow to 3.");
           printf("1.- nazwa programu, 2.- wybrana opcja obslugi sygnalow, 3.-numer sygnalu ");
           exit(1);
         }

    int  nr_syg=atoi(argv[2]); //zamienia lancuch na int
 
      void obsluga(int nr_syg)
          {
            printf("Przechwycenie i obsluga wlasna sygnalu. ");
            printf("Nr sygnalu to: %d. \n",nr_syg); 
          }
     
     switch(*argv[1])
           {
              case 'd':
                 if(signal(nr_syg,SIG_DFL)==SIG_ERR)
                    { perror("Blad przy wykonaniu operacji domyslnej dla sygnalu "); 
                    exit(1);
                    }
                 else 
                   {
                   printf("Wykonanie operacji domyslnej dla sygnalu. ");
                   printf("Nr sygnalu to: %d. \n",nr_syg);
                  }
                     
              break;

              case 'i':
                  if(signal(nr_syg,SIG_IGN)==SIG_ERR)
                    { perror("Funkcja ma problem z SIGIGN "); 
                      exit(1);
                    }              
               else {
                    printf("Sygnal zignorowany. ");
                  printf("Nr sygnalu to: %d. \n",nr_syg);
                     }
              break;

              case 'p':
                    if(signal(nr_syg,obsluga)==SIG_ERR)
                    { perror("Blad przy wykonaniu operacji wlasnej dla sygnalu. "); 
                    exit(1);
                    }
                    
                
              break;
              


           }



 sleep(20);

 return 0; 
}
