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
	char tab_z[ROZ_BUF];			//tworze tablice zapisu
	int zapisz;
	srand(time(NULL));			//inicjuje generator liczb losowych
	int usleep();				//deklaracja funkcji usleep();
	
	sem_prod = semDecl(11);			//tworze semafor dla producenta
	sem_kons = semDecl(12);			//tworze semafor dla konsumenta

	semInit(sem_prod, ROZ_BUF);		//inicjuje semafor producenta wartoscia rozmiaru buforu
	semInit(sem_kons, 0);			//inicjuje semafor konsumenta wartoscia 0
	
	shmid = shmCreate(11, ROZ_PAM);		//tworze pamiec dzielona
	adres = shmAt(shmid);			//dowiazuje segment pamieci dzielonej
	
	bufor = adres;				//umieszczam bufor w pamieci dzielonej
	
	bufor -> size = ROZ_BUF;
	bufor -> end = 0;
	
	int magazyn = open("magazyn.txt", O_RDONLY);				//tworzymy deskryptor do pliku magazyn.txt
	if(magazyn == -1){							//sprawdzam czy mozna otworzyc plik magazyn.txt
		perror("magazyn");
		exit(1);
	}
	
	printf("\nProducent rozpoczyna prace...\n");
	while(1){

		if((zapisz = (int)read(magazyn, tab_z, (bufor -> size))) == 0) break;
			
		do{
			semP(sem_prod);					//opuszczam semafor producenta
			usleep(rand()%1000000);	
		
			bufor -> buf[bufor -> end] = tab_z[bufor -> end];
			tab_z[bufor -> end] = '\0';
			bufor -> end = (bufor -> end+1) % bufor -> size;
		
		
			//printf("\n===%c===\n", tab_z[bufor -> end]);
	
			semV(sem_kons);
			//semInfo(sem_kons);
		}while(bufor -> end != 0);
	
		printf("\nPrzeslano do buforu: %s\n", bufor -> buf);
	}
	
	printf("\nProducent zakonczyl prace!\n");
	wait(0);			//czekam na koniec procesu konsumenta
	shmDt(adres);			//usuwam dowiazanie do pamieci dzielonej
	close(magazyn);			//usuwam deskryptor do magazynu
	
	return 0;
}
	
