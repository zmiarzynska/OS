#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "procinfo.h"

int main(int argc, char * argv[])
{
  if(argc!=3)
         {
           printf("Zla liczba argumentow. Prawidlowa liczba argumentow to 3.");
           printf("1.- nazwa programu, 2.- wybrana opcja obslugi sygnalow, 3.-numer sygnalu ");
           exit(1);
         }
  int  nr_syg=atoi(argv[2]);
  int i;
  if(signal(nr_syg,SIG_IGN)==SIG_ERR)
     {
       perror("Blad w funkcji signal dla macierzystego.");
       exit(1);
     }

 
 
  for(i=0;i<3;i++)
     {
        switch(fork())
         {  
           case -1:
           perror("Blad w wykonaniu funckji fork");
            exit(1);
           break;     
           
           case 0:
            execl("./obsluga.x","obsluga.x",argv[1],argv[2],NULL);
               perror("Blad w funkcji exec.");
               exit(1);
            break;
            default:
             sleep(2);
                      
             break;
         }
	

     }
             

                

                 if(kill(0,nr_syg)==-1)
                 perror("Blad w trakcie uzycia funkcji kill ");
             


 return 0;
}
