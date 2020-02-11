#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "msg.h"
#define MAX 10


//typedef struct {
  //      long mtype; /*typ komunikatu*/
    //    char mtext[123]; /*tekst komunikatu*/
	//	//char msg[123];
//}komunikat;


int main(int argc, char const *argv[])
{	
	int msqid = msgCreate(11);
	komunikat wiadomosc;
	int pid;
	//long msg_type=(long)getpid();
//wiadomosc.mtype=msg_type;
	//wiadomosc.mtype=1;
	pid=wiadomosc.etykieta;
	while(1){
	msgRecv(msqid, wiadomosc.mtext, wiadomosc.mtype); //zmienic mtype
	printf("Tresc brzmi: %s\n PID: %d\n",wiadomosc.mtext, pid );
}
	return 0;
}