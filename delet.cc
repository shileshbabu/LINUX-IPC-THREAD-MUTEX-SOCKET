#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
	int fd[2];
	int result;
	if(pipe(fd)==0)
		//printf("pipe is created successfully\n");
	//	printf("fd[0]==%d",fd[0]);
		//printf("fd[1]==%d",fd[1]);
	result=fork();
	//printf("value of result=%d\n",result);
 return 0;
}
