 #include <sys/types.h>
 #include <sys/socket.h>
 #include <stdio.h>
 #include <sys/un.h>
 #include <unistd.h>
 #include <stdlib.h>
 int main()
 {
 int sockfd;
 int len,res;
 struct sockaddr_un address;
 int result;
 char buff[15],ch = 'A';
 sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
 address.sun_family = AF_UNIX;
 strcpy(address.sun_path, "server_connect");
 len = sizeof(address);
 result = connect(sockfd, (struct sockaddr *)&address, len);
 if(result == -1) 
 {
 	printf(" client1  error ");
 }
 res=write(sockfd, &ch, 1);
 read(sockfd, buff, 1);
 printf("char from server%s = %d\n",buff,res);
 close(sockfd);
 return 0;
 }

