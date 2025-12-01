#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8000);  // Same port as server
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    const char* message = "Hello from UDP Client";

    // Send message to server
    sendto(clientSocket, message, strlen(message), 0,
           (sockaddr*)&serverAddr, sizeof(serverAddr));

    cout << "Message sent to server." << endl;

    char buffer[1024];
    int serverLen = sizeof(serverAddr);

    // Receive response
    memset(buffer, 0, sizeof(buffer));
    recvfrom(clientSocket, buffer, sizeof(buffer), 0,
             (sockaddr*)&serverAddr, &serverLen);

    cout << "Server replied: " << buffer << endl;

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
