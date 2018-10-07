 #include "header.h" 
 #include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <sys/shm.h>
 int main()
 {
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
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
	//shared_stuff->written_by_you = 0;
	while(running) 
	{
		 //if (shared_stuff->written_by_you) 
		//{
			printf("your data: %s", shared_stuff->some_text);
			sleep(4); // make the other process wait for us
			//shared_stuff->written_by_you = 0;
			if(strncmp(shared_stuff->some_text, "end", 3) == 0) 
			{
				running = 0;
			}	
	}	
	if (shmdt(shared_memory) == -1) 
	{
		printf("shmdt failed\n");
		goto OUT;
	}
	if (shmctl(shmid, IPC_RMID, 0) == -1) 
	{
		printf("error in deleting shmid\n");
		goto OUT;
	}
	return 0;
OUT:
	return -1;
  }
