#include "request.h"
#include "header.h"
int main(int argc,char*argv[])
{
	struct request s;
     	int wfd,rfd,sum;
     	int count;
     	if(argc!=3)
     	{
     	 	printf("error\n");
      		goto OUT;
     	}
     	printf("In %s\n",__FILE__);
     	rfd=atoi(argv[1]);
     	wfd=atoi(argv[2]);
     	printf("In %s\trfd:%d , wfd:%d\n",__FILE__, rfd, wfd);
     	read(rfd,&s,sizeof(struct request));
     	printf("s.opr2=%d\t s.opr3=%d \n",s.opr2,s.opr3);
     	sum=s.opr2+s.opr3;
     	printf("sum=%d \n",sum);
     	count=write(wfd,&sum,sizeof(int));
        printf("count = %d \n",count);
        return 0;
   OUT:
        return -1;
     }                          
