#define ILOSC_BAJTOW 100
#include<stdio.h> 
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h> 
#include<unistd.h>
#include<stdlib.h> 
 


int main(int argc, char *argv[])
    {
       
       
       char *buf;
        
        
       FILE   *wskaznik_plik;
       
       int desk;
  
       buf=malloc(ILOSC_BAJTOW);
        
        if(buf==NULL){
              perror("Problem z malloc");
              exit(1);
          }
        
       desk=open(argv[1],O_WRONLY,0666);

          if(desk==-1){
            perror("Blad w funkcji open"); 
            exit(1);
            }
       
           wskaznik_plik=fopen("magazyn.txt","r");

           if(wskaznik_plik==NULL){
              perror("Nie udalo sie utworzyc pliku");
              exit(1);
            }  
       while(fgets(buf,ILOSC_BAJTOW,wskaznik_plik)!=NULL){
         
         
          
             if((write(desk,buf,ILOSC_BAJTOW))==-1){
                  perror("Blad przy uzyciu funkcji write");
                   exit(1);
               }
             usleep(40000);
           printf("Do potoku: %s",buf);
        }
      fclose(wskaznik_plik);
      close(desk);
      
     
          

         
      
      return 0; 
    }
