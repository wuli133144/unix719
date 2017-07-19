#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<stdarg.h>
#include<syslog.h>


#define MAXLINE   1024

static void log_doit(int ,int ,int,const char *,va_list ap);


extern int log_to_stderr;


void log_open(const char *cmd,int opention,int facility){
    if(log_to_stderr==0){
        openlog(cmd,opention,facility);
    }
}

void log_ret(const char *fmt,...){
    va_list ap;
    va_start(ap,fmt);
    log_doit(1,errno,LOG_ERR,fmt,ap);
    va_end(ap);
}

static void log_doit(int errnoflag,int error,int prop,const char *fmt,va_list ap){
       char buf[MAXLINE];
       vsnprintf(buf,MAXLINE-1,fmt,ap);

       if(errnoflag){
           snprintf(buf+strlen(buf),MAXLINE-strlen(buf)-1,":%s",strerror(errno));
       }
       strcat(buf,"\n");
       if(log_to_stderr){
           fflush(stderr);
           fputs(buf,stderr);
           fflush(errno);
       }else{
           syslog(prop,"%s",buf);
       }

}