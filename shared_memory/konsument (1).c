#define _SVID_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include "shmem.h"
#include "sem.h"

#define ROZ_PAM 1024
#define ROZ_BUF 11

int main(){
	
	int sem_prod;
	int sem_kons;
	int shmid;
	void *adres;
	cykliczny *bufor;			//tworze wskaznik do struktury
	char tab_o[ROZ_BUF];			//tworze bufor zapisu
	int petla;
	srand(time(NULL));			//inicjuje generator liczb losowych
	int usleep();				//deklaracja funkcji usleep();
	
	sem_prod = semDecl(11);			//tworze semafor dla producenta
	sem_kons = semDecl(12);			//tworze semafor dla konsumenta
	
	shmid = shmOpen(11);			//otwieram pamiec dzielona
	adres = shmAt(shmid);			//dowiazuje segment pamieci dzielonej
	
	bufor = adres;				//umieszczam bufor w pamieci dzielonej
	
	FILE *schowek = fopen("schowek.txt", "w");				//sprawdzam czy mozna otworzyc plik schowek.txt
	if(schowek == NULL){
		perror("schowek");
		exit(1);
	}
	
	bufor -> size = ROZ_BUF;
	bufor -> beg = 0;
	
	petla = 1;
	printf("\nKonsument rozpoczyna prace...\n");
	sleep(1);
	
	while(petla){

		sleep(1);
		//printf("-------> HALO x1\n\n");
		
		do{
			//printf("-------> HALO x2\n\n");
			
			semP(sem_kons);			//opuszczam semafor konsumenta
			usleep(rand()%1000000);	
			//sleep(1);
			
			tab_o[bufor -> beg] = bufor -> buf[bufor -> beg];
			
			if(tab_o[bufor -> beg] == '\0'){
				petla = 0;
				break;
			}
			//printf("\n===%c===\n", tab_o[bufor -> beg]);
			
			bufor -> beg = (bufor -> beg+1) % bufor -> size;
			semV(sem_prod);			//podnosze semafor producenta
		}while(bufor -> beg != 0);
		
		printf("\nOdebrano z buforu: %s\n", tab_o);
		
		if(fputs(tab_o, schowek) == EOF){		//kopiuje dane z buforu do schowka
			perror("funkcja fputs");
			exit(1);
		}
	}
	
	printf("\nKonsument zakonczyl prace!\n");
	shmDt(adres);			//usuwam dowiazanie do pamieci dzielonej
	fclose(schowek);		//usuwam deskryptor do schowka
	
	return 0;
}
