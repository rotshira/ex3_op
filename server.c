#include <sys/socket.h>
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <string.h> 
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>


#define SERVER_PORT 5060 
#define SIZE 67536

// double total = 0;

int main() {
    	int serverSocket = -1;
    	struct sockaddr_in serverAddress, clientAddress;
    	int enableReuse = 1;
    	socklen_t clientAddressLen = sizeof(clientAddress);
    	int clientSocket = -1;
    	socklen_t length;

    	char buffer[SIZE] = {0};  
       
    	// Creating socket 
    	printf("create server socket\n");
    	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        	printf("Error! create server socket failed with error code : %d", errno);
    	} 
	    // To prevents error of- address is already in use.
    	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR , &enableReuse, sizeof(enableReuse)) < 0) {
        	printf("setsockopt() failed with error code : %d", errno);
    	} 
    	
    	bzero(&serverAddress, sizeof(serverAddress)); 
        serverAddress.sin_family = AF_INET; 
    	serverAddress.sin_addr.s_addr = INADDR_ANY; 
    	serverAddress.sin_port = htons(SERVER_PORT); 
    	// Bind the socket to the port with any IP at this port
		printf("bind\n");
    	if (bind(serverSocket, (struct sockaddr *)&serverAddress,  sizeof(serverAddress)) == -1) {
        	printf("Error! bind failed with error code : %d", errno);
        	close(serverSocket);
        	return -1;
    	} 
    	printf("Bind() success\n");
    	
		// Make the socket listening;
		if (listen(serverSocket, 5) < 0){ //500 is a Maximum size of queue connection requests
		//number of concurrent connections 
	        printf("listen() failed with error code : %d", errno);
        	close(serverSocket);
        	return -1;
	    }
	    while (1)
		{
			memset(buffer, 0, sizeof(buffer));
			int bytesReceived = 0;
			int i = 0;
			while(i<1){
				memset(&clientAddress, 0, sizeof(clientAddress));
				clientAddressLen = sizeof(clientAddress);
				clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
				if (clientSocket == -1){
					printf("accept failed with error code : %d", errno);
					close(serverSocket);
					return -1;
				}
				// counting the time of the recving of the file
				int sum =0;
				while( (bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0 ) {
					if(strcmp(buffer,"LOCAL") == 0){
				
						printf("Exit Server\n");
						close(clientSocket);
						close(serverSocket);
					}
				sleep(2);
				printf("%s", buffer);
				memset(buffer, 0, sizeof(buffer));
				}
			}
		}
		
		
}