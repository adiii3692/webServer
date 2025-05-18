//  Header file with all the methods to create, bind and use sockets
#include <sys/socket.h>
//  Header file with all the methods that help define socket configurations
#include <netinet/in.h>
//  Standard Libraries imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//  The socket we create for the basic definition of a socket
int server_fd;
//  The socket that is used to listen to accept connections, read and write data, then closed
int new_socket;
//  Struct to define the socket configurations
struct sockaddr_in address;
//  int to store the size of the address
int addrlen = sizeof(address);
//  PORT Number of the socket
#define PORT 8080

int main(int argc, const char** argv){
    /*  AF_INET for using IPv4
        SOCK_STREAM for using TCP/IP 
        0 for using IP as the protocol
    */
    if ((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("Cannot create socket");
        exit(EXIT_FAILURE);
    }


    memset((char*)&address, 0, sizeof(address));

    //  Assign sin_family variable the AF_INET value for IPv4
    address.sin_family = AF_INET;
    /* htons converts a short integer (eg. port no) to a network representation */
    address.sin_port = htons(PORT);
    /* htonl converts a long integer (eg. address) to a network representation */
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    //  Bind the socket configurations to the socket
    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //  Listen tells the socket to accept connections with a backlog of 3 processes in the queue
    if (listen(server_fd, 3) < 0){
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }

    //  Constantly accept connections, read and write data before closing the connection
    while(1){
        printf("-------ACCEPTING CONNECTIONS--------\n");
        //  Create a new socket based on the server_fd socket configurations to accept connections
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0){
            perror("Accept Failed");
            exit(EXIT_FAILURE);
        }
        
        //  Read data and store it in a char buffer
        printf("-------READING DATA-------\n");
        char buffer[3000] = {0};
        long readData = read(new_socket,buffer,3000);
        //  Print the data
        printf("%s\n",buffer);

        //  Write data 
        printf("-------WRITING DATA--------\n");
        const char* message = "Hello From AD's Web Server!";
        write(new_socket,message,strlen(message));

        //  Close the socket
        printf("-------CLOSING SOCKET--------\n");
        close(new_socket);
    }

    //  Exit
    return 0;
}