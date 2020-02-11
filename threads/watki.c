#define _REENTRANT
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int counter=0;
int x=2,y=1,d=10;
void* nowa(void* wsk){

 int counter_n;
 
// thid=(int*)wsk;
 printf("\033[35m");
// printf("\033[%d;%dHSekcja prywatna\n",x,y);
  
 printf(" Watek - sekcja prywatna\n"); 

   pthread_mutex_lock(&mutex);
   
   counter_n=counter;
 printf(" \033[36m");
 printf("\033[%d;%dHTutaj %d. sekcja krytyczna po opuszczeniu muteksu\n",x,y+27,x-1);
// printf("Tutaj sekcja krytyczna po opuszczeniu muteksu\n");

   counter_n++;
   x++; 
   sleep(1);
   counter=counter_n;
   pthread_mutex_unlock(&mutex);
    
   printf("\033[35m");//Watek po sekcji krytycznej\n");

 return NULL;
}

int main(){
 printf("\033c");
 
 int i;
   printf("Glowny proces: tworze w swoim obrebie watki: \n");
 
 pthread_t thid[10]; 
 void *wsk=NULL;

for(i=0;i<10;i++){
      
  
      if(pthread_create(&thid[i],NULL,nowa,wsk)!=0){
               printf("Blad w funkcji pthread_create");
               exit(1);
      }
}
  
 
 for(i=0;i<10;i++){
      if(pthread_join(thid[i],NULL)!=0){
               printf("Blad w pthread_join");
               exit(1);

      }
 
 }
   printf("Czekam na watki.Licznik %d\n",counter);
   
 



 /* 

 void pthread_exit(void *status);


 
 int pthread_detach();

 pthread_mutex_init();
*/



return 0;

}
