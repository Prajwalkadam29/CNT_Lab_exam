#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET serverSocket, clientSocket;
    char buffer[1024] = {0};

    // 1. Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Setup server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // 4. Listen
    listen(serverSocket, 1);
    cout << "TCP Server waiting for connection..." << endl;

    // 5. Accept a client
    int addrSize = sizeof(serverAddr);
    clientSocket = accept(serverSocket, (sockaddr*)&serverAddr, &addrSize);

    // 6. Receive message
    recv(clientSocket, buffer, 1024, 0);
    cout << "Client says: " << buffer << endl;

    // 7. Send reply
    const char* msg = "Hello from TCP Server";
    send(clientSocket, msg, strlen(msg), 0);

    // 8. Close sockets
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
