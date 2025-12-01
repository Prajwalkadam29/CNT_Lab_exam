#include <iostream>
#include <winsock2.h>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buffer[1024];

    while (true) {
        string msg;
        cout << "Enter operation (sin 30, cos 45, tan 90): ";
        getline(cin, msg);

        sendto(clientSocket, msg.c_str(), msg.length(), 0,
               (sockaddr*)&serverAddr, sizeof(serverAddr));

        int len = sizeof(serverAddr);
        memset(buffer, 0, sizeof(buffer));

        recvfrom(clientSocket, buffer, sizeof(buffer), 0,
                 (sockaddr*)&serverAddr, &len);

        cout << "Result: " << buffer << endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
