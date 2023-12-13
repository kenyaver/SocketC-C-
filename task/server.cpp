#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#define DEFAULT_ADDRESS "127.0.0.1"

int connection[8];


int main(){
    int port;
    printf("input port: ");
    scanf("%d", &port);

    sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(DEFAULT_ADDRESS);
    addr.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, (sockaddr*)&addr, addrLen);
    listen(sock, 20);
    
    int new_connect;
    for(int i = 0; i < 20; i++){
        new_connect = accept(sock, (sockaddr*)&addr, &addrLen);
        if(new_connect != 0){
            printf("new connection: %d", i);
            send(new_connect, "200-OK", 7, 0);
        }
    }
}