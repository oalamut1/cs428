#include <unistd.h>

#include <stdio.h>

#include <sys/socket.h>

#include <stdlib.h>

#include <netinet/in.h>

#include <string.h>

#include <cstring>

#include <string>

#include <iostream>

#include <time.h>

#include <sys/types.h>

#include <arpa/inet.h>

#include <errno.h>

#include <thread>

#include <chrono>

#include <sys/time.h>

#include <ctime>

using namespace std;

//#define PORT 12001
#define PORT 12000

int main()

{
	int sockfd, n;
	socklen_t len;
	char buffer[1024];
	struct sockaddr_in servaddr, cliaddr; 

	// Initialize server address
        memset(&servaddr, 0, sizeof(servaddr));
	// Initialize client address
	memset(&cliaddr, 0, sizeof(cliaddr));
	
        // Server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; // localhost
	servaddr.sin_port = htons(PORT); // port number
	
        // Keeps track of ping
	// Default value of 1
	int id = 1;

	// For loop allows client to revieve pings
	int pings = 10;
	for (int i = 0; i < pings; i++) {
	  // Create UDP socket
	  // SOCK_DGRAM used for UDP packets
	  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	  // Define timeout 
	  struct timeval timeout;
	  // Set timeout to 1 second 
	  timeout.tv_sec = 1;
	  timeout.tv_usec = 0;
	  // If statement to catch failing timeout
	  if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
	    printf("setsocket failed\n");
	  // Time client sends ping to server
	  // starts counting before sendto
	  struct timeval now;
	  gettimeofday(&now, NULL);
	  int milli2 = now.tv_sec / 1000;
	  char newerBuffer[80];
	  strftime(newerBuffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&now.tv_sec));
	  char currentTime2[84] = "";
	  sprintf(currentTime2, "%s:%03d", newerBuffer, milli2);
	  // Ping is sent to server by client
	  sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	  // Ping is receieved back from server by client 
	  n = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *) &cliaddr, &len);
	  // Notify user of which ping is being sent 
	  printf("Ping Message Count %d\n", id);
	  // id keeps track of ping messages reveived  
	  id++;
	  // Duration it takes for the client to receieve ping from server
	  struct timeval later;
	  gettimeofday(&later, NULL);
	  int milli = later.tv_usec / 1000;
	  char newBuffer[80];
	  strftime(newBuffer, 80, "Y-%m-%d %H:%M:%S", localtime(&later.tv_sec));
	  char currentTime[84] = "";
	  sprintf(currentTime, "s:%03", newBuffer, milli);
	  // Finds difference between when client sends ping and when client recieves it back
	  // Round trip calculation
	  // Microseconds is most precise
	  int microseconds = (later.tv_sec - now.tv_sec) * 1000000 + ((int)later.tv_usec - (int)now.tv_usec);
	  // Milliseconds derived from microseconds
	  int milliseconds = microseconds / 1000;
          // Seconds derived from seconds 
          int seconds = milliseconds / 1000;
          // if statement to check if packet was lost 	 
          // n == 1 means packet lost 
	  if(n == 1) {
	    printf("Packet Was Lost\n");
          } else {
	  // If packet was not lost display trip time   
	    printf("Round Trip Time Delay In Microseconds(ms): %i\n", microseconds);
	  }
	  // Visual divider
          printf("-----------\n");
          // checks for timeout      
          if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
            printf("Request timed out!");
	    // Close socket
            close(sockfd);
          }
    }
    // Close socket
    close(sockfd);
    return 0;	
}	  
	  
	  
