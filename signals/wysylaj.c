#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "procinfo.h"

 int main(int argc, char *argv[])
{
     if(argc!=3)
         {
           printf("Zla liczba argumentow. Prawidlowa liczba argumentow to 3.");
           printf("1.- nazwa programu, 2.- wybrana opcja obslugi sygnalow, 3.-numer sygnalu ");
           exit(1);
         } 

     int a; 
     int  nr_syg=atoi(argv[2]);
     switch(a=fork())
           {
            case 0:
             
               execl("./obsluga.x","obsluga.x",argv[1],argv[2],NULL);
               perror("Blad w funkcji exec");
               exit(1);
            break;

            case -1:
              perror("Blad w funkcji fork."); 
              exit(1); 
            break;

            default:
              sleep(2);
             
            break;
          }

           if(kill(a,0)==-1)
                {perror("proces nie istnieje");
                 exit(1);
                }
              if(kill(a,nr_syg)==-1)
                { perror("Blad w trakcie uzycia funkcji kill ");
                 exit(1);
                }






 return 0;
}
