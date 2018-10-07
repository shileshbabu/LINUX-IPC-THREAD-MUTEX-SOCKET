#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main()
{
int ffd;
//int file_pipes[2];
int fd[2];
char some_data[]="shil";
char buffer[BUFSIZ+1];
pid_t fork_result;
memset(buffer,'\0',sizeof(buffer));
if(pipe(fd)==0)
 fork_result=fork();
     if(fork_result==0)
      {
     
     
        printf("fd1=%d\n",fd[1]);
     //ffd=read(fd[0],buffer,BUFSIZ);
     printf("fd0=%d\n",fd[0]);
      }
     else
     {
//	ffd=write(fd[1],some_data,strlen(some_data));
        printf("fd1=%d\n",fd[1]);
    
     printf("fd0=%d\n",fd[0]);}
 return 0;
  }
