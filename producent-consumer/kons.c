#define ILOSC_BAJTOW 100
#include<stdio.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> 
#include<unistd.h>
#include<stdlib.h> 
#include <sys/wait.h>

int main(int argc, char* argv[])
{

   char *buf2;
     
    FILE   *wskaznik_plik2;
   
    buf2=malloc(ILOSC_BAJTOW);

    int desk2=open(argv[1],O_RDONLY,0666);

      if(desk2==-1){
        perror("Nie udalo sie utworzyc pliku");
        exit(1);
       }

      wskaznik_plik2=fopen("schowek.txt", "w");
     
        if(wskaznik_plik2==NULL){
          perror("Nie udalo sie otworzyc pliku 'schowek.txt'");
         }
     while(read(desk2,buf2,ILOSC_BAJTOW)>0){
           fputs(buf2,wskaznik_plik2);
           printf("  Z potoku: %s",buf2);
           usleep(40000);
           }
   
   fclose(wskaznik_plik2);
   close(desk2);  
       

 return 0; 
}
