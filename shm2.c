 #include "header.h" 
 #include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <sys/shm.h>
 int main()
 {
 	int run = 1;
 	void *shared_memory = 0;
 	struct shared_use_st *shared_stuff;
 	char buffer[BUFSIZ];
 	int shmid;
 	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	printf("shmid=%d\n",shmid);
 	if (shmid == -1) 
 	{
		printf("shmget failed\n");
		goto OUT;
 	}
 	shared_memory = shmat(shmid, (void *)0, 0);
 	if (shared_memory == (void *)-1) 
	{
		 printf("shmat failed\n");
		 goto OUT;
	}
 	printf("Memory attached at %X\n", shared_memory);
 	shared_stuff = (struct shared_use_st *)shared_memory;
 	while(run) 
 	{
	printf("please enter your value\n ");
	fgets(buffer, BUFSIZ, stdin);
	strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
//	shared_stuff->written_by_you = 1;
	if (strncmp(buffer, "end", 3) == 0) 
	{
		 run = 0;
	}
 	}
/////////////////
	if (shmdt(shared_memory) == -1) 
	{
		printf("shmdt failed\n");
		goto OUT;
	}
	return 0;
OUT:
	return -1;
 }

