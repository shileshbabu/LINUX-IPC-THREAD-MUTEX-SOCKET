#include "header.h"
#include "request.h"
int main(int argc,char*argv[])
{
	int *stack,i,no;
	int count;
	char buff[8];
	no=atoi(argv[1]);
	struct request val;
	char rfd[6],wfd[6];
	char file[4][15]={"./pro_request","pro_request","./pro_adder","pro_adder"};
	int choise=0;
	for(i=1;i<=no;i++)
	{
		stack=(int*)realloc(stack,sizeof(int)*2*i);
		if(stack==NULL)
		{
			printf("error in reallic\n");
			goto OUT;
		}
		pipe(stack+(i*2)-2);
		sleep(2);
		printf("wfd or rfd in this process\n");
		printf("rfd[%d]=%d wfd[%d]=%d\n",(i*2)-2,*(stack+(i*2)-2),(2*i)-1,*(stack+(i*2)-1));}
		/*pid_t pid;
		pid=fork();
		if(pid==0)
		{
		 	printf("child process\n"); 
		 	sprintf(rfd,"%d",*(stack+i*2-2));
		 	sprintf(wfd,"%d",*(stack+i*2-1));
                        //execl("./pro_request","pro_request", rfd, wfd, NULL);
                        execl(file[i*2-2],file[i*2-1], rfd, wfd, NULL);
	 	}
		if(pid>0)
		{
	       		printf("Server Process\n");
			if(choise==0)
			{
				if(read(*(stack+i*2-2),&val,sizeof(struct request)))
				{	
		 			printf("val.opr1=%c\n",val.opr1);
	         			printf("val.opr2=%d\n",val.opr2);
	         			printf("val.opr3=%d\n",val.opr3);
		  		}
			//close(*(stack+i*2-2));
			choise++;
			} 
			if(choise==1)
			{ 
               			printf("%s\n", __FILE__);
		 		write(*(stack+i*2-1),&val,sizeof(struct request));
                 		sleep(5);
				close(*(stack+i*2-1));
                 		count=read(*(stack+i*2-2),&buff,sizeof(int));
		 		printf("%s; sum = %d\n",__FILE__, buff);
	        		//exit(EXIT_SUCCESS);
	        	}
		
	      } 
	     // choise++;   
			//close(*(stack+i*2-2));
      }*/
              return 0;
 OUT:
 	return -1;  
 }
	
