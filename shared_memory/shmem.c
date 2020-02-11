#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int shmCreate(int id, int size){

//proces tworzy (rezerwuje) segment pamieci
key_t key;
 key =ftok(".",id);
  
 int shmid=shmget(key,size,IPC_CREAT|0600);
 
 if(shmid==-1){
 
   perror("Blad w funkcji shmget (utworzenie)");
   exit(1);
 }
 printf("Utworzylem segment o id %d\n",shmid);

return shmid;
}

int shmOpen(int id){
// uzyskaj dostep do pamieci dziel.
  key_t key;
 key =ftok(".",id);
  
 int shmid=shmget(key,0,IPC_CREAT|0600);
 
 if(shmid==-1){
 
   perror("Blad w funkcji shmget (dostep)");
   exit(1);
 }
 printf("Uzyskalem dostep o id %d\n",shmid);
 return shmid;
}

void shmRm(int shmid){

//usuwa segment
  int usun_seg=shmctl(shmid,IPC_RMID,0);
  if(usun_seg==-1){

   perror("Blad w funkcji shmctl(usuwanie)\n");
   exit(1);
  }
   printf("Segment usunieto\n");

}

void* shmAt(int shmid){

  // dowiazuje go 

  void *wsk_seg=shmat(shmid,NULL,0); //zwraca wskaznik do segmentu pamieci dzielonej potrzebny do usuniecia dowiazania

  //if(wsk_seg==-1){

    //perror("Blad w funkcji shmat");
   // exit(1);
  //}

 printf("Dowiazanie utworzone. Wskaznik wynosi: %d\n",&wsk_seg);

}

void shmDt(void *adres){
//kazdy proces osobno korzystajacy usuwa dowiazanie
 int usun_dow=shmdt(adres);

 if(usun_dow==-1){

  perror("Blad w fukncji shmdt");
  exit(1);
 }

 printf("Usunieto dowiazanie.\n");

}

int shmSize(int shmid){
 struct shmid_ds buf;
 if((shmctl(shmid, IPC_STAT, &buf))==-1){
 
   perror("Blad w funkcji shmSize");
   exit(1);
 }

 return buf.shm_segsz;
}

void shmInfo(int shmid){
 struct shmid_ds buf;
 shmctl(shmid,IPC_STAT,&buf);
 printf("%d",buf.shm_perm);
 printf("%d",buf.shm_atime);
 printf("%d",buf.shm_dtime);
 printf("%d",buf.shm_ctime);
 printf("%d",buf.shm_cpid);
 printf("%d",buf.shm_nattch);
 

}

//int main()
//{
 //int shmid=shmCreate(10,100);
 // shmid=shmOpen(10);
// void* wsk=shmAt(shmid);
// printf("shmid wynosi %d",shmid); 
// size_t cos=shmOpen(shmid);
// printf("costam %d",cos);
//return 0;
//}

