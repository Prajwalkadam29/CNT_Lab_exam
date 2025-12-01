#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr, clientAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);    // UDP PORT
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to local IP + port
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    cout << "UDP Hello Server running on port 8000..." << endl;

    char buffer[1024];
    int clientLen = sizeof(clientAddr);

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        // Receive UDP message
        recvfrom(serverSocket, buffer, sizeof(buffer), 0,
                 (sockaddr*)&clientAddr, &clientLen);

        cout << "Client says: " << buffer << endl;

        // Send back reply
        const char* reply = "Hello from UDP Server";
        sendto(serverSocket, reply, strlen(reply), 0,
               (sockaddr*)&clientAddr, clientLen);

        cout << "Reply sent.\n";
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
