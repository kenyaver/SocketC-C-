#include "check.h"

int main(){
    int socket = socketCheck(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT1);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    socklen_t sizeServer = sizeof(serverAddr);
    int ret = bindCheck(socket, reinterpret_cast<sockaddr*>(&serverAddr), sizeServer);

    listenCheck(socket, 5);
    int fd = acceptCheck(socket, reinterpret_cast<sockaddr*>(&serverAddr), &sizeServer);

    char buffer[BUFFER_SIZE];
    int mread;

    while(true){
    // mread = read(fd, buffer, BUFFER_SIZE);
    if(mread == -1){
        perror("read msg failed\n");
        exit(EXIT_FAILURE);
    }
    // if(mread == 0){
    //     printf("END OF FILE occured\n");
    // } else {
        recv(fd, buffer, BUFFER_SIZE, 0);
        // printf("message is %d bytes\n", mread);
        std::cout << buffer;
    // }
    }
    sleep(1);
    close(socket);
    close(fd);
    return 0;
}