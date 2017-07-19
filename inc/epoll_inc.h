
#include<sys/epoll.h>
#include<errno.h>
#include<string.h>
#include<sys/time.h>
#include<sys/select.h>

#include<sys/stat.h>
#include<fcntl.h>

#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<stddef.h>
#include<stdarg.h>



#define EPOLL_SIZE  100


//jackwu 

#define UNIX_error(msg)do{                      \
    fprintf(stderr,"%s,%s",msg,strerror(errno));\
    exit(0);                                    \
    }while(0)


#define UNIX_warn(msg)do{                                            \
    fprintf(stderr,"%s,%s",msg,strerror(errno));\
    return;                                     \
    }while(0)



/*@select start@*/
int Select(int maxfd,           \
          fd_set *readset,      \
          fd_set *writeset,     \
          fd_set *exceptionset, \
          struct timeval *tmout){
  int rval;
  if((rval=select(maxfd,readset,writeset,exceptionset,tmout))<0){
      UNIX_error("select error");
  }else if(rval==0){
      UNIX_warn("Time out!");
  }
  return rval;
}
/*@select end@*/


/*@epoll_create start@*/
int Epoll_create(int size){
   
     int  fd;
     if((fd=epoll_create(size))<0){
         UNIX_error("epoll_create error!");
     }
     return fd;
}
/*@epoll_create start@*/

/*@epoll_ctl@*/
int Epoll_ctl(int efd,int op,int fd,struct epoll_event *event){
      int rval;
      if((rval=epoll_ctl(efd,op,fd,event))==-1){
          UNIX_error("epoll_ctl error");
      }
      return rval;
}
/*@epoll_ctl end@*/

/*@epoll_wait start@*/
int Epoll_wait(int efd,struct epoll_event *even,int maxeven,int timeout){
      int fdmax;
      if((fdmax=epoll_wait(efd,even,maxeven,timeout))<0){
          UNIX_error("epoll_wait");
      }
      return fdmax;
}
/*@epoll_wait end@*/
