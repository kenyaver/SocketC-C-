#include "check.h"

int main(){
    int client = socketCheck(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT1);
    // inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    inet_ptonCheck(AF_INET, (char*)"192.168.0.255", &serverAddr.sin_addr);
    socklen_t addrLen = sizeof(serverAddr);
    connectCheck(client, reinterpret_cast<sockaddr*>(&serverAddr), addrLen);
    char buffer[BUFFER_SIZE];
    std::cin.getline(buffer, BUFFER_SIZE);
    send(client, buffer, BUFFER_SIZE, 0);
    close(client);
}