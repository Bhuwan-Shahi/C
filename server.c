#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

//This the main program of the server program .it declare variable of the socket file discrptor
//The new file descriptor , the address of the server, the length of the address
//A buffer for reciviving data and a message to send to the client

int main(int argc, char const * argv[]){
    int server_fd , new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello form server";

    //creating socket file descriptor
    //Thsi code creates a socket file descriptor using the sockte() system
    // call, It uses the AF_INET address familly to specify IPv4.
    //  SOCK STREAM as the socket type for the  TCP  connection can be SOCK DGRAM  for UDP conneciton, and 0 as the protocol argument.


    //int socket (int domain , int type , int protocol);


    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //Setup address structure for the server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);


    //int bind(int socketfd, struct  socketaddr *ay_addr, socklent_t addrlen)
    // Bind the socket to the address
    if(bind(server_fd , (struct  sockaddr *)&address , sizeof (address)) <0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    };
    

    //Start listening for incoming connections
    //int listen(int scoketfc, int backlog) -> backlog is a max length of the pending conncetion
    if (listen(server_fd , 3)< 0){
        perror("listen fialed");
        exit(EXIT_FAILURE);
    }


    //Accept incoming connesctions and handle them
    if ((new_socket == accept(server_fd , (struct  sockaddr *)&address,(socklen_t *)&addrlen))<0){
        perror("accept failed");
        exit(EXIT_FAILURE);
    }


    // Read data from teh client
    int valread = read(new_socket , buffer , 1024);
    printf("%s/n",buffer);



    //Send a message back to the client
    send(new_socket, hello, strlen(hello),0);
    printf("helloo message sent\n");


    return 0;
  


}