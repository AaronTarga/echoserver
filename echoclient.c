#include<stdio.h>   
#include<string.h>  
#include<sys/socket.h>  
#include<arpa/inet.h>

#define MAX 1000
#define REP 2000   

int main(int argc , char *argv[])
{
	int soc;
    	struct sockaddr_in server;
    	char msg[MAX];
	char reply[REP];

    	soc = socket(AF_INET , SOCK_STREAM , 0);

    	server.sin_addr.s_addr = inet_addr("127.0.0.1");
    	server.sin_family = AF_INET;
    	server.sin_port = htons( 8882 );

    	connect(soc , (struct sockaddr *)&server , sizeof(server));
    

    	while(1)
    	{
        	printf("Message: ");
        	fgets(msg,MAX,stdin );
		if(msg[0] == 27) 
			return 0;
        
        	send(soc , msg , strlen(msg), 0);

    		bzero(reply,REP);
       		if( recv(soc , reply, REP, 0) < 0)
        	{
           	 break;
        	}

      		printf("%s \n",reply);
    	}

    	close(soc);
    	return 0;
}
