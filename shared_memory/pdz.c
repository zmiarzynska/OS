#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int shmget(key_t key, size_t size, int shmflags);

char* shmat (int shmid, char *shmaddr, int shmflags);
shmid - id zwracany przez shmget()
shmaddr - adres pamieci lub NULL

int shmctl(int shmid, int cmd , struct shmid_ds *buf);
shmid_ds - systemowa struktura w <sys/types.h>

char* shmdt(char* shmaddr_2);
shmaddr_2 - wskaźnik zwracany przez shmat 

bufor cykliczny mniej więcej można sobie wyobrazić tak że mamy 5 komórek dostępu i każda ma jakiś rozmiar (np.10 bajtów) i to działa na zasadzie paska ładowania (każda komórka przechodzi po kolei) w programie to będzie tablica [1][2][3][4][5] i to będzie tak jakby nasze koło
są też wskaźniki HEAD TAIL HEAD to ostatnie miejsce gdzie było coś zapisane a TAIL to ostatnie które było odczytane 


ma być #define LICZBA_KOMOREK 5
#define ROZMIAR_KOMORKI 10

struct SegmnetPD
{
char bufor[LICZBA_KOMOREK][ROZMIAR_KOMORKI];
int head,tail;
}


PRODUCENT
//semafory PROD,KONS
SegmentPD towar
zapis
while(1){
   P(PROD); //opuszczenie
   bufor[head]=dane;
   head = (head+1)%LICZBA_KOMOREK;
   V(KONS); //podniesienie
}

KONSUMENT
odczyt
while(1){
   P(KONS);
   towarkons=bufor[tail];
   tail = (tail+1)%LICZBA_KOMOREK;
   V(PROD);
}


robimy na 2 semaforach ( jeden do zapisu drugi do odczytu)






