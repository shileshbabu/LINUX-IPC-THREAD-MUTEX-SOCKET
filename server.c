 #include <sys/types.h>
 #include <sys/socket.h>
 #include <stdio.h>
 #include <sys/un.h>
 #include <unistd.h>
 #include <stdlib.h>
 int main()
 {
 	int server_fd, client_fd;
	char ch;
 	int server_len, client_len;
 	struct sockaddr_un server_address;
 	struct sockaddr_un client_address;
 	unlink("server_connect");

 	server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
 	server_address.sun_family = AF_UNIX;
 	strcpy(server_address.sun_path, "server_connect");
 	server_len = sizeof(server_address);
 	bind(server_fd, (struct sockaddr *)&server_address, server_len);
	listen(server_fd, 5);
	while(1) 
	{
		char buff[]="shilesh";
		printf("server waiting\n");
		client_len = sizeof(client_address);
		client_fd = accept(server_fd,(struct sockaddr *)&client_address, &server_len);
		read(client_fd,&ch,1);

		printf("server_data=%c\n",ch);

		write(client_fd, buff, 5);
		close(client_fd);
	}
		close(server_fd);
}

