#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

int main(int argc, char *argv[])
{
   int semid=semDecl(11); 
   //semInit(semid,1);
   switch(*argv[1]){

           case 'i':
           
            semInit(semid,1);
            semInfo(semid);
            
           break;
            
           case 'r':
             
             semRm(semid);
           semInfo(semid);
           break;

           case 'p':
            
           semP(semid);
           semInfo(semid);
           break;
 
           case 'v':
           
           semV(semid);
           
           semInfo(semid);
           break;
  
           case 'z':
            
	   semZ(semid);
           semInfo(semid);
           break;

           case 'q':
           
           semInfo(semid);
           break;
       } 
    
 return 0;
}
