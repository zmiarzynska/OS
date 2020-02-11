#include<stdio.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) // argv[1] dla nazwy potoku
{
  
   if(mkfifo(argv[1], 0744)==-1){ //stworzenie potoku
// 2 procesy potomne: 1) dla konsumenta 2)dla producenta
     perror("BLad w mkfifo");
     exit(1);
    }
   switch(fork())
     {
       case -1:
          perror("Blad przy uzyciu funkcji fork");        
         break;

      case 0:
         execl("./kons.x","kons.x",argv[1],NULL); 
         break;
     
    }

     switch(fork())
     {
       case -1:
          perror("Blad przy uzyciu funkcji fork");        
         break;

      case 0:
         execl("./prod.x","prod.x",argv[1],NULL);
         break;


     }
// 2 razy wait dla kazdego z potomnych
    if(wait(0)==-1){
            perror("Blad w funkcji wait");
            exit(0);       
         }

     if(wait(0)==-1){
            perror("Blad w funkcji wait");
            exit(0);       
         }


     unlink("./argv[1]");

return 0;
}
