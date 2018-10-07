 #include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <fcntl.h>
 #include <limits.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #define FIFO_NAME "/tmp/fifo_shillu"
 #define FIFO_NAME1 "/tmp/fifo_shillu1"
 #define BUFFER_SIZE PIPE_BUF
 int main()
 {
 	int pipe_fd;
 	int res;
 	int open_mode = O_RDONLY;//---------------------reader
	int open_mode1= O_WRONLY;
 	char buffer[BUFFER_SIZE + 1]; 
	char buffer1[BUFFER_SIZE + 1]="345";
 	memset(buffer, '\0', sizeof(buffer));
 	printf("Process %d opening FIFO O_RDONLY\n", getpid());
 	pipe_fd = open(FIFO_NAME, open_mode);
 	printf("Process %d result %d\n", getpid(), pipe_fd);
 	if (pipe_fd < 0) 
	{
		printf("error in pipe_fd\n");
		goto OUT;
	}
 	res = read(pipe_fd, buffer, BUFFER_SIZE);
 	close(pipe_fd);
	printf("buffer=%s\n",buffer);
 	printf("Process %d finished, %d= res value\n", getpid(), res);//------------------------------------write
	printf("__write __mode__\n");
	sleep(1);
	res = mkfifo(FIFO_NAME1, 0777);
        if (res != 0)
        {
                printf("Could not create fifo %s\n", __FILE__);
        }
        printf("Process %d opening FIFO O_WRONLY\n", getpid());
        pipe_fd = open(FIFO_NAME1, open_mode1);
        printf("Process %d result %d\n", getpid(), pipe_fd);
        if (pipe_fd <0)
        {
        printf("error in opening file\n");
        }
        res = write(pipe_fd, buffer1, BUFFER_SIZE);
        if (res == -1)
        {
                printf("Write error on pipe\n");
                goto OUT;
        }
        close(pipe_fd);
        printf("res=%d buffer_res=%s\n",res,buffer1);
        printf("Process %d finished\n", getpid());
	return 0;
OUT:
	return -1;
 }

