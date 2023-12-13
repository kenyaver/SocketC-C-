#include "check.h"

int socketCheck(int domain, int type, int protocol){
    int res = socket(domain, type, protocol);
    if(res == -1){
        perror("socket failed;(\n");
        exit(EXIT_FAILURE);
    }
    return res;
}

int bindCheck(int socket, sockaddr* sockadr, socklen_t addrLen){
    int res = bind(socket, sockadr, addrLen);
    if(res == -1){
        perror("bind socket failed;(\n");
        exit(EXIT_FAILURE);
    }
    return res;
}

void listenCheck(int socket, int backlog){
    int res = listen(socket, backlog);
    if(res == -1){
        perror("listen socket failed;(\n");
        exit(EXIT_FAILURE);
    }
}

int acceptCheck(int socket, sockaddr* addr, socklen_t* addrLen){
    int res = accept(socket, addr, addrLen);
    if(res == -1){
        perror("accept failed\n");
        exit(EXIT_FAILURE);
    }
    return res;
}

void connectCheck(int sockfd, sockaddr* addr, socklen_t addrLen){
    int res = connect(sockfd, addr, addrLen);
    if(res == -1){
        perror("connect failed\n");
        exit(EXIT_FAILURE);
    }
}

void inet_ptonCheck(int af, char* src, void* dst){
    int res = inet_pton(af, src, dst);
    if(res == 0){
        printf("inet_pton failed: src not valid\n");
        exit(EXIT_FAILURE);
    }
    if(res == -1){
        perror("inet_pton failed: af not valid\n");
        exit(EXIT_FAILURE);
    }
}