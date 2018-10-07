#include "request.h"
#include "header.h"
int main(int argc,char*argv[])
{
	struct request list;
	int wfd,rfd;
	int count;
     	if(argc!=3)
     	{
      		printf("Insufficient Arguments\n");
   		goto OUT;
     	}
      	printf("In: %s\n", __FILE__);
     	rfd=atoi(argv[1]);
     	wfd=atoi(argv[2]);
     	list.opr1='+';
     	list.opr2=5;
     	list.opr3=9;
     	count=write(wfd,&list,sizeof(struct request));
     	printf("count value=%d\n",count);
     		return 0;
     		OUT:
     		       	return -1;
     		       	}
