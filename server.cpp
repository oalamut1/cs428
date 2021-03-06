// UDP Pinger

// Must have this server running before you can run the UDP Pinger Client code

#include <iostream>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <time.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <ctime>
#include <sys/time.h>
#include <chrono>

#define PORT	 12000


int main() { 
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr, cliaddr;

	char* ping = (char*)"Ping";
	
	// Create a UDP socket
	// Notice the use of SOCK_DGRAM for UDP packets
	//sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Fill server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number

        int id = 1;
        // Sends pings 
	int pings = 10;
	for(int i = 0; i < pings; i++) {
	  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	  struct timeval timeout;
	  timeout.tv_sec = 1;
	  timeout.tv_usec = 0;
	  //if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)) < 0)
	    }

	    
	// Bind the socket with the server address 
	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	
	// random generator
	srand(time(0));

        while (1) {
		//Receive the client packet along with the address it is coming from
		n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 
			MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buffer[n] = '\0';

		//If a random number in the range of 0 to 10 is less than 4,
		//we consider the packet lost and do not respond
		if (rand()%10 < 4) continue;

		//Otherwise, the server responds
		sendto(sockfd, (const char *)buffer, strlen(buffer), 
			MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
	}
	return 0; 
} 
