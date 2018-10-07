#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
int main(int argc,char*argv[])
{
printf("test in one\n");
int i = atoi (argv[1]);

printf("test in one\n");

printf("i=%d\n",i);
/*ch=argv[0];
printf("ch=%c\n",ch);
ch=argv[1];
printf("ch=%c\n",ch);
ch=argv[2];
printf("ch=%c\n",ch);*/
return 0;
}


