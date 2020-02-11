/*Przy pomocy pamięci dzielonej oraz semaforów systemu UNIX zaimplementować problem ,,Producenta i Konsumenta’’
dla N-elementowego bufora cyklicznego (tzn. po dojściu do końca bufora wracamy na jego początek) umieszczonego w pamięci dzielonej,
 gdzie elementem bufora jest pewna ustalona porcja bajtów. Dla zademonstrowania, że nie doszło do utraty ani zwielokrotnienia towaru,
 niech Producent pobiera ,,surowiec’’ (np. porcje bajtów lub liczby typu int) z pliku tekstowego magazyn.txt i wstawia go jako towar
do bufora, a Konsument niech umieszcza pobrany z bufora towar w innym pliku tekstowym schowek.txt. Po zakończeniu działania programów
 (wyczerpaniu zasobów ,,surowca“) oba pliki tekstowe powinny być identyczne. Oba procesy niech drukują odpowiednie komunikaty na ekranie,
 w tym towar, który przesyłają. Do zasymulowania różnych szybkości działania programów użyć funkcji usleep np. z losowym czasem usypiania.
 Należy użyć dwóch semaforów, pierwszy blokuje zapis (producent) gdy bufor cykliczny jest pełny, drugi blokuje odczyt (konsument) gdy bufor
 cykliczny jest pusty. Struktura bufora cyklicznego, która znajduje się w pamięci dzielonej może mieć postać:

*/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h> /* EXIT_FAILURE; */
#include <sys/types.h>
#include "libshmem.h"
#include "libsem.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#define SIZE 100 //rozm pam dzielonej?
 #define BUFOR 50 // rozmiar bufora

	typedef struct{ 
   int size;            // Całkowity rozmiar bufora 
   int beg;             // Pierwszy element do odczytu 
   int end;             // Element za ostatnim zapisanym elementem 
   char buf[30];  // Dane, własny typ 'towar' może być równoważny np. 'int' 
   }cykliczny;  // bufor to wsk do strunktury

char tab_zapis[BUFOR]; /*tablica do zapisywania danych do schowka*/ 

 int main(int argc, char const *argv[])
 {
	printf("KONSUMENT \n");
	srand(time(NULL));	
	
 	cykliczny *bufor; //wskaźnik do struktury 

 	printf("DZIAŁA\n");

	//SEMAFORY
	int sem1 = semDecl(10); // semafor pierwszy - producenta
	int sem2 = semDecl(11); // semafor drugi - konsumenta
	


	//PAMIEC DZIELONA
	
	int shmid = shmOpen(11);			//otworzenie
	void *memory = shmAt(shmid);			//dowiązanie   				
	bufor=memory;
	printf("Umieszczono bufor w pamięci dzielonej\n");
	

	(*bufor).size = BUFOR;
	(*bufor).beg = 0;
	printf("DZIALAAA\n");
 
	FILE *schowek;
	schowek = fopen("schowek.txt", "w");	
	int petla=1;
   		printf("\n KOPIOWANIE START\n");


   		while(petla){

		do{
			semP(sem1);	//obniza BUFOR				
			
			usleep(rand()%1000000);	
			//sleep(1);
			
			tab_zapis[bufor -> beg] = bufor -> buf[bufor -> beg];
			
			if(tab_zapis[bufor -> beg] == '\0'){
				petla = 0;
				break;
			}
			printf("\n===%c===\n", tab_zapis[bufor -> beg]);
			
			bufor -> beg = (bufor -> beg+1) % bufor -> size;
			
	
			semV(sem2); //PODNOSI producent
			//semInfo(sem_kons);
		}while(bufor -> beg != 0);
	
		printf("\nOdebrano z buforu: %s\n", tab_zapis);
		
		fputs(tab_zapis, schowek);
	}

	
		printf("\nProducent - KONIEC\n");
wait(0);			//czekam na koniec procesu konsumenta
shmDt(memory);			//usuwam dowiazanie do pamieci dzielonej
fclose(schowek);			//zamykam schowek
	


 	return 0;
 }
