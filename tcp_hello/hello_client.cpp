#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET clientSocket;
    char buffer[1024] = {0};

    // 1. Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Setup server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Connect
    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // 4. Send message
    const char* msg = "Hello from TCP Client";
    send(clientSocket, msg, strlen(msg), 0);

    // 5. Receive reply
    recv(clientSocket, buffer, 1024, 0);
    cout << "Server says: " << buffer << endl;

    // 6. Close
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
