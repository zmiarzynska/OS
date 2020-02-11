#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "sem.h"
#include <unistd.h>

int main(int argc, char *argv[]){
    printf("To ja, prog\n");
     
     
      int s=atoi(argv[1]);
    

do{         
      printf("PID : %d. Prog potomny: Przed sekcja krytyczna\n",(int)getpid());
        
      semP(s);
   
      printf("PID : %d. Prog potomny: Tu sekcja krytyczna\n",(int)getpid());
      semInfo(s);
          
      semV(s);
    
      printf("PID : %d. Prog potomny: Po sekcji krytycznej\n",(int)getpid());
 
      

   }while(1);     

 return 0;
}

