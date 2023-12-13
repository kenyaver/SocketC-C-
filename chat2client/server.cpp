#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <thread>

#define ERROR_S "SERVER ERROR: "
#define DEFAULT_PORT 1601
#define PORT_CLIENT2 1602
#define BUFFER_SIZE 1024
#define CLIENT_CLOSE_CONNECTION_SIMBOL '#'

// int server;
// int server2;
sockaddr_in server_address;

bool client_connection_closed(const char* msg){
    for(int i = 0; i < strlen(msg); i++) {
        if(msg[i] == CLIENT_CLOSE_CONNECTION_SIMBOL){
            return true;
        }
    }
    return false;
}

void handle_client(int client1, int client2){
    socklen_t size = sizeof(server_address);
    int server1 = accept(client1, reinterpret_cast<sockaddr*>(&server_address), &size);
    int server2 = accept(client2, reinterpret_cast<sockaddr*>(&server_address), &size);

    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    while(true){
    std::thread r([&]{
        recv(server1, buffer1, BUFFER_SIZE, 0);
        std::cout << buffer1;
        send(server2, buffer1, BUFFER_SIZE, 0);
    });
    if(client_connection_closed(buffer1)){
        return;
    }

    std::thread r2([&]{
        recv(server2, buffer2, BUFFER_SIZE, 0);
        std::cout << buffer2;
        send(server1, buffer2, BUFFER_SIZE, 0);
    });
    if(client_connection_closed(buffer2)){
        return;
    }

    r.join();
    r2.join();
    }
}

int main(int argc, char const* argv[]) {
    int client1;
    int client2;

    client1 = socket(AF_INET, SOCK_STREAM, 0);
    if(client1 < 0) {
        std::cout << ERROR_S << "establishing socket error";
        exit(0);
    }

    client2 = socket(AF_INET, SOCK_STREAM, 0);
    if(client2 < 0){
        std::cout << ERROR_S << "establishing socket error\n";
        exit(1);
    }

    std::cout << "SERVER: Socket for server was succesfully created\n";
    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    int ret_client1 = bind(client1, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address));
    if(ret_client1 < 0){
        std::cout << ERROR_S << "binding connection1 failed\n";
        return -1;
    }
    listen(client1, 1);
    
    server_address.sin_port = htons(PORT_CLIENT2);
    int ret_client2 = bind(client2, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address));
    if(ret_client2 < 0){
        std::cout << ERROR_S << "binding connection2 failed\n";
        return -1;
    }

    std::cout << "SERVER: Listening clients...\n";
    
    listen(client2, 1);

    handle_client(client1, client2);
    std::cout << "Goodbye\n";
    return 0;
}   