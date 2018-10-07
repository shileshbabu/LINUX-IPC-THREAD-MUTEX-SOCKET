 #include <stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>
 void *thread_function(void *arg);
 char message[] = "helloshilesh";
 int main() 
 {
 	int res;
	pid_t pid;
	int i;
	void *thread_result;
	pthread_t a_thread[10];
	for(i=0;i<10;i++)
	{
 	res =  pthread_create(&a_thread[i], NULL, thread_function,(void *)&i);
 	if (res != 0) 
	{
 		perror("Thread creation failed");
 		goto OUT;
 	}
	sleep(2);
	}
	//printf("Message is now %s\n", message);
	//printf("pid_of_main=%d\n",getpid());
	printf("Waiting for thread to finish...\n");
	for(i=0;i<10;i++)
	{
	res = pthread_join(a_thread[i], &thread_result);
	printf("pid_of_function=%d\n",getpid());
	if (res != 0) 
	{
	printf("Thread join failed\n");
	goto OUT;
	}
	}
	printf("thread_result=%s",(char*)thread_result);
	printf("main thread successful\n");
	return 0;
 OUT:
	return -1;
 }
 void *thread_function(void *arg) 
 {
	int i;
	int j;
	i=*(int*)arg;
	while(1)
	{
	printf("thread creat[%d]\n", i);
//	if(i>=0)
//	{
	//	pthread_exit("thread 5 is finished now\n");}
	//printf("pid_of_function=%d\n",getpid());
	sleep(2);
	}
 }
