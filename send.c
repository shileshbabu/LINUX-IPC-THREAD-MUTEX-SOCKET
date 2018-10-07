 #include <unistd.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <fcntl.h>
 #include <limits.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #define FIFO_NAME "./fifo"
 #define BUFFER_SIZE PIPE_BUF
 int main()
 {
 	int pipe_fd;
 	int res;
 	int open_mode = O_WRONLY;//---------------------write
 	char buffer[BUFFER_SIZE + 1]="shilesh"; 
 	memset(buffer, '\0', sizeof(buffer));

	res = mkfifo(FIFO_NAME, 0777);
        if (res != 0)
        {
                printf("Could not create fifo %s\n", __FILE__);
        }
        pipe_fd = open(FIFO_NAME, open_mode);
        printf("Process %d result %d\n", getpid(), pipe_fd);
        if (pipe_fd <0)
        {
        printf("error in opening file\n");
        }
        res = write(pipe_fd, buffer, BUFFER_SIZE);
        if (res == -1)
        {
                printf("Write error on pipe\n");
                goto OUT;
        }
        //close(pipe_fd);
        printf("res=%d buffer_res=%s\n",res,buffer);
        printf("Process %d finished\n", getpid());
        close(pipe_fd);
	return 0;
OUT:
	return -1;
 }
/*
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char * myfifo = "./myfifo";
    char buf[MAX_BUF];
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("Received:%s\n", buf);
    close(fd);
    return 0;
}*/

