//  Header file with all the methods to create, bind and use sockets
#include <sys/socket.h>
//  Header file with all the methods that help define socket configurations
#include <netinet/in.h>

//  The socket we create
int server_fd;
//  Struct to define the socket configurations
struct sockaddr_in address;
//  PORT Number of the socket
const int PORT = 8080;

int main(){
    /*  AF_INET for using IPv4
        SOCK_STREAM for using TCP/IP 
        0 for using IP as the protocol
    */
    if ((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("Cannot create socket");
        return 0;
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
        return 0;
    }

    
}