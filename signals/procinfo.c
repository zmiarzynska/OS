#include <stdio.h>
#include "procinfo.h"
#include <sys/types.h>
#include <unistd.h>

int procinfo(const char *name)
    { 
      int pgid=(int)getpgid(0);
    

     printf("NAZWA: %s, PID %d, PPID %d,UID %d, GID %d,PGRP %d,PGID %d\n",name,(int)getpid(),(int)getppid(),(int)getuid(), (int)getgid(),getpgrp (),pgid);


     if(pgid==-1)
       {  perror("Blad w funkcji getpgid ");
       }

     
   
    return 0;

    }
