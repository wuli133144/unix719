


#ifndef __UNIX_ERROR__H
#define __UNIX_ERROR__H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

void unix_error(const char *msg){
    fprintf(stderr,"%s:%s\n",msg,strerror(errno));
    exit(0);
}

void posix_error(int code,const char *msg){
     fprintf(stderr,"s:%s\n",msg,strerror(code));
     exit(0);
}

#endif
