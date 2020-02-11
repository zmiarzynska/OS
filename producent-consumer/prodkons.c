#define ILOSC_BAJTOW 100
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/param.h>


 void prod(int *filedes)
    {
     printf("Jestem producentem.\n");
     void *buf;   
     FILE   *wskaznik_plik;
     buf=malloc(ILOSC_BAJTOW);
     close(filedes[0]); // zamykanie deksrypt. pliku strumi
     wskaznik_plik= fopen("magazyn.txt","r"); 
       while(wskaznik_plik!=NULL){
         //perror("Blad przy uzyciu funkcji fopen"); //pobiera surowiec z magazyn.txt

     
     
            if(fgets(buf,ILOSC_BAJTOW,wskaznik_plik)==NULL) {  // wstawia go jako towar do potoku
            perror("Blad lub koniec pliku");
             exit(0);
              }
            
           if(write(filedes[1],buf,ILOSC_BAJTOW)==-1){
               perror("Blad przy uzyciu funkcji write.\n");
              exit(1);
              }
         sleep(2); // czekanie na kons().
        } 

      

      fclose(wskaznik_plik); // zamyka plik
      close(filedes[1]); // zamknij deskr
      if(wait(0)==-1)
        perror("Blad przy uzyciu funkcji wait");

    }
 void kons(int *filedes)
      {
         printf("Jestem konsumentem.\n");
         void *buf;
         FILE   *wskaznik_plik;
         close(filedes[1]);

         buf=malloc(ILOSC_BAJTOW);
         
         wskaznik_plik=fopen("schowek.txt","w");
         
        while(read(filedes[0],buf,ILOSC_BAJTOW)>0)
          {
          // perror("Wystapil blad podczas przy uzyciu funkcji read");
           //exit(1);
             
 

            fputs(buf,wskaznik_plik);  // umieszcza pobrany z potoku plik w schowek.txt
            sleep(1);
          }  
     fclose(wskaznik_plik);
     close(filedes[0]);
     
     }

int main()
{
  int filedes[2];
  if(pipe(filedes)==-1){
     
     perror("Blad przy uzyciu funkcji pipe"); 
      exit(1);     
  
     }





  switch(fork())
      { 
         case -1:
             perror("Blad przy uzyciu funkcji fork");
             exit(1);
            break;

         case 0:
            kons(filedes);
           break;
            
         default:
           prod(filedes);
          break;   
      }



 
return 0;
}
