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
 	int open_mode = O_RDONLY;    //---------------------read
 	char buffer[BUFFER_SIZE + 1]; 
 	memset(buffer, '\0', sizeof(buffer));
        pipe_fd = open(FIFO_NAME, open_mode);
        printf("Process %d result %d\n", getpid(), pipe_fd);
        if (pipe_fd <0)
        {
        printf("error in opening file\n");
        }
        res = read(pipe_fd, buffer, BUFFER_SIZE);
        if (res == -1)
        {
                printf("Write error on pipe\n");
                goto OUT;
        }
        //close(pipe_fd);
        printf("res=%d   buffer_read==%s\n",res,buffer);
        printf("Process %d finished\n", getpid());
        close(pipe_fd);
	return 0;
OUT:
	return -1;
 }
/*
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char * myfifo = "./myfifo";
    mkfifo(myfifo, 0666);
    fd = open(myfifo, O_WRONLY);
    write(fd, "Hi", sizeof("Hi"));
    close(fd);
    unlink(myfifo);
    return 0;
}
*/
