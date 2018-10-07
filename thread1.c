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
	pthread_t a_thread;
 	res =  pthread_create(&a_thread, NULL, thread_function, message);
 	if (res != 0) 
	{
 		perror("Thread creation failed");
 		goto OUT;
 	}
	printf("Message is now %s\n", message);
	printf("pid_of_main=%d\n",getpid());
	//sleep(1);
	return 0;
 OUT:
	return -1;
 }
 void *thread_function(void *arg) 
 {
	sleep(0);
	printf("pid_of_function=%d\n",getpid());
	printf("Argument was %s\n", (char *)arg);
	sleep(8);
	
 }
