#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "msg.h"
#define MAX 10

//typedef struct {
  //      long mtype; /*typ komunikatu*/
  //      char mtext[123]; /*tekst komunikatu*/

//}komunikat; //=wiadomosc

//char odbior[];
int main(int argc, char const *argv[])
{

int pid; 
int msqid = msgCreate(11); //tworze kolejke 


komunikat wiadomosc; 
pid=getpid();
wiadomosc.etykieta=pid;
wiadomosc.mtype=1;
//wiadomosc.mtype=1; //identyfkuje kolejke
while(1){
printf("PODAJ KOMUNIKAT:\n");
fgets(wiadomosc.mtext, sizeof(wiadomosc.mtext), stdin);
printf("Tresc brzmi: %s",wiadomosc.mtext);
//lokacja=(long)getpid(); /*zwraca PIDa kom*/
//wiadomosc.lokacja=lokacja;
//strncpy(wiadomosc.mtext, "ANGELIKA", MAX);

msgSend(msqid,wiadomosc.mtext); /*wysyla komunikat*/
printf(" PID %d\n",pid );}
//msgRecv(msqid,&wiadomosc, lokacja); /*odbiera wiadomosc*/
//printf("Komunikat: %s\n", lokacja);



	return 0;
}