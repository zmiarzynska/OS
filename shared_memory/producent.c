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
#include <string.h>
#define SIZE 100 //rozm pam dzielonej
#define BUFOR 50 // rozmiar bufora

	typedef struct{ 
   int size;            // Całkowity rozmiar bufora 
   int beg;             // Pierwszy element do odczytu 
   int end;             // Element za ostatnim zapisanym elementem 
   char buf[30];  // Dane, własny typ 'towar' może być równoważny np. 'int' 
   }cykliczny;  // bufor to wsk do strunktury

char tab_wczyt[BUFOR]; /*tablica do wczytywania danych z magazynu*/

 int main(int argc, char const *argv[])
 {	
 	srand(time(NULL));
	printf("PRODUCENT \n");
	int magazyn;
	int bajty;
	
 	int id; //id segmentu pamięci dzielonej
 	cykliczny *bufor; //wskaźnik do struktury 

 	printf("DZIAŁA\n");

	//SEMAFORY
	int sem1 = semDecl(10); // semafor pierwszy - producenta
	int sem2 = semDecl(11); // semafor drugi - konsumenta
	semInit(sem1,0); //semafor producenta zainicjowany wartościa bufora (ilość dostepnych zasobów - ilość bajtów)
	semInit(sem2, BUFOR); //semafor konsumenta zainicjowany wartościa 0


	//PAMIEC DZIELONA
	void *memory;
	id=shmCreate(11,SIZE); /*Tworzy segment pamięci dzielonej o rozmiarze size bajtów.*/
    printf("Utworzono segment : id %d, o rozmiarze %d\n", id, SIZE);
	memory=shmAt(id); /*Dowiązuje segment pamięci dzielonej shmid. Zwraca adres odwzorowania.*/	       				
	bufor=memory;
	printf("Umieszczono bufor w pamięci dzielonej\n");
	(*bufor).size = BUFOR;
	(*bufor).end = 0;
	printf("DZIALAAA\n");
 	

	magazyn=open("magazyn.txt", O_RDONLY);

	printf("%d\n", magazyn);

   		printf("\n Producent start\n");

   		while(1) {

				if((bajty = read(magazyn, tab_wczyt, (bufor -> size))) == 0) break; // koniec pliku albo błąd
			
		do{
			
			semP(sem2);					//opuszczam semafor producenta O
			usleep(rand()%1000000);	
			
			bufor -> buf[bufor -> end] = tab_wczyt[bufor -> end];
			//tab_wczyt[bufor -> end] = '\0';
			bufor -> end = (bufor -> end+1) % bufor -> size;
		
		
			printf("\n %c \n", tab_wczyt[bufor -> end]);
	
			semV(sem1); // podnosze BUFOR
			//semInfo(sem_kons);
		}while(bufor -> end != 0);
		printf("\nPrzeslano do buforu: %s\n", bufor -> buf);
	}
	
		printf("\nProducent - KONIEC\n");
wait(0);			//czekam na koniec procesu konsumenta
shmDt(memory);			//dowiązanie usunięte
close(magazyn);			//zakniecie deskryptora
	


 	return 0;
 }






