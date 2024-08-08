#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main(int argc, char const *argv[]){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    // Create a socket for the client
    if((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
        printf("/n Socket creation error\n");
        return -1;
    }

    // Set up server address and port
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
        printf("Invalid address / address not supported \n");
        return -1;
    }

    // Connect to the server
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nConnection failed\n");
        return -1;
    }

    // Send a message to the server
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Read the server's response
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    return 0;
}
