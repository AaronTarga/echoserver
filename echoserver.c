#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>   
#include <unistd.h>  

int main(int argc, char *argv[]) {
	int socket_descriptor , c , read, client_socket;
	struct sockaddr_in server, client ;
	char msg[2000]; 

	int option = 1;
	socket_descriptor = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	setsockopt(socket_descriptor,SOL_SOCKET,SO_REUSEADDR,&option, sizeof(option));

	server.sin_family = AF_INET;
   	server.sin_addr.s_addr = inet_addr("127.0.0.1");
   	server.sin_port = htons( 8882 );

	bind(socket_descriptor,(struct sockaddr *)&server , sizeof(server));
	
	listen(socket_descriptor, 5);

	c = sizeof(struct sockaddr_in);

	while(1) {

		client_socket = accept(socket_descriptor, (struct sockaddr *)&client, (socklen_t*)&c);
		if(fork() == 0) {
			while(1) {
			read = recv(client_socket,msg,2000,0);
			send(client_socket,msg,read,0);
				if(msg[0] == 27) {
					close(client_socket);
				}
			}
		}
	}
	return 0;
}
