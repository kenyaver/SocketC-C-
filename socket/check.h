#ifndef CHECK_H
#define CHECK_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#define PORT1 1500
#define BUFFER_SIZE 1024

// check created socket and return created socket
int socketCheck(int domain, int type, int protocol);
// check bind socket and return binded socket
int bindCheck(int socket, sockaddr* sockadr, socklen_t addrLen);
// check listen 
void listenCheck(int socket, int backlog);
// check accept and return accepted socket
int acceptCheck(int socket, sockaddr* addr, socklen_t* addrLen);
// check connect and connect socket to addr
void connectCheck(int sockfd, sockaddr* addr, socklen_t addrLen);
// check inet_pton and write addr in <server>.sin_addr
void inet_ptonCheck(int af, char* src, void* dst);
#endif