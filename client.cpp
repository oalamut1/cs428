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

#define PORT 12000

int main(int argc, char const *argv[])

{

    int server_fd, new_socket, valread;

    struct sockaddr_in address;

    int opt = 1;

    int addrlen = sizeof(address);

    char buffer[1024];

    //= {0};

    string hello = "Hello from server";

    cout << "hi" << endl;

    // Creating socket file descriptor

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)

    {
      cout << "if1" << endl;

        perror("socket failed");

        exit(EXIT_FAILURE);

    }

      

    // Forcefully attaching socket to the port 8080

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,

                                                  &opt, sizeof(opt)))

    {
      cout << "if2" << endl;

        perror("setsockopt");

        exit(EXIT_FAILURE);

    }

    address.sin_family = AF_INET;

    address.sin_addr.s_addr = INADDR_ANY;

    address.sin_port = htons( PORT );

    cout << address.sin_port << endl;  

    // Forcefully attaching socket to the port 8080

    if (bind(server_fd, (struct sockaddr *)&address,

                                 sizeof(address))<0)

    {
      cout << "if3" << endl;

        perror("bind failed");

        exit(EXIT_FAILURE);

    }

    if (listen(server_fd, 3) < 0)

    {
      cout << "if4" << endl;

        perror("listen");

        exit(EXIT_FAILURE);

    }

    cout << "1 loop left" << endl;

    /*    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
      {
	cout << "if5" << endl;
        perror("accept");

        exit(EXIT_FAILURE);
	} */

    cout << "before valread" << endl;
    valread = read( new_socket , buffer, 1024);
    cout << "after valread" << endl;

    cout << "got here" << endl;
    
    //    printf("%s\n",buffer );
    cout << buffer << endl;

    cout << "before send" << endl;
    send(new_socket , (const char *) buffer , sizeof(buffer) , 0 );
    cout << "after send" << endl;
    //    printf("Hello message sent\n");

    cout << "hello sent" <<endl;
    return 0;

}
