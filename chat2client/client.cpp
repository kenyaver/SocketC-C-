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

#define SERVER_IP "192.168.0.255"
#define DEFAULT_PORT 1601
#define ERROR_C "CLIENT:"
#define SERVER_CLOSE_CONNECTION_SIMBOL '#'
#define BUFFER_SIZE 1024

bool client_connection_closed(const char* msg){
    for(int i = 0; i < strlen(msg); i++) {
        if(msg[i] == SERVER_CLOSE_CONNECTION_SIMBOL){
            return true;
        }
    }
    return false;
}

int main(int argc, const char* argv[]){
    int client;

    sockaddr_in server_address;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if(client < 0){
        std::cout << ERROR_C << "socket connection failed\n";
        exit(1);
    }
    int port;
    std::cout << "enter port(1601 - 1602): ";
    std::cin >> port;

    server_address.sin_port = port;
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr);

    std::cout << "client: socket created\n";

    int ret = connect(client, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address));
    if(ret == 0){
        std::cout << "=> connected to server "
                << inet_ntoa(server_address.sin_addr) << ":" << port << std::endl;
    }

    char buffer[BUFFER_SIZE];
    std::thread r([&]{
        recv(client, buffer, BUFFER_SIZE, 0);
        std::cout << buffer;
    });
    r.detach();
    while(true){
        std::cout << "Enter message: \n";
        std::thread r1([&]{
            recv(client, buffer, BUFFER_SIZE, 0);
            std::cout << buffer;
        });
        if(client_connection_closed(buffer)){
            break;
        }

        std::cin.getline(buffer, BUFFER_SIZE);
        send(client, buffer, BUFFER_SIZE, 0);
        if(client_connection_closed(buffer)){
            break;
        }
        r1.join();
    }
    close(client);
    std::cout << "GoodBye...\n";
    return 0;
}