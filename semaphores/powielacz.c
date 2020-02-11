#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>  
#include <sys/sem.h>
#include "sem.h"


int main(int argc, char *argv[]){

 // tworze i inicjuje semafor
      int s=semDecl(12);
  int a=atoi(argv[2]);
      semInit(s,1);
     printf("Powielacz: Semafor zainicjowany\n");

int j;
 
char t[10];
   sprintf(t,"%d",s);

for(j=0;j<a;j++){
  switch(fork()){
   
           case -1: 
            perror("Blad w funkcji fork");
            exit(1);
            break;

           case 0:
            
            if(execl("./prog.x","prog.x",t,NULL)==-1) perror("Blad w exec");
             printf("Jestem tutaj,po exec\n");
           break;

          default:
            printf("pid defau: %d,I ja tez, powielacz default \n",(int)getpid());
           usleep(1000);
          
          break;


    }
}
    usleep(5000);

    if(signal(15,SIG_IGN)==SIG_ERR){

       perror("Blad w funkcji signal");
       exit(1);
      }

    if(kill(0,15)==-1){
      perror("Blad w funkcji wait");
      exit(1);
     } 

for(j=0;j<a;j++){
 if(wait(NULL)==-1){
                perror("Blad w funkcji wait\n");
                exit(1);
             }
 }
    
   semRm(s); //usuwam semafor. 
   
 return 0;

}
