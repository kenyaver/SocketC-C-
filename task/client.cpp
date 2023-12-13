#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

#define DEFAULT_ADDRESS "127.0.0.1"

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    int port;
    printf("input port: ");
    scanf("%d", &port);

    sockaddr_in addr;
    socklen_t addrLen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(DEFAULT_ADDRESS);
    addr.sin_port = htons(port);

    int ret = connect(sock, (sockaddr*)&addr, addrLen);
    if(ret == 0){
        char buffer[32];
        recv(sock, buffer, 32, 0);
        printf("%s", buffer);
    } else {
        printf("fail\n");
    }
    sleep(10);
}