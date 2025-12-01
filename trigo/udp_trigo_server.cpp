#include <iostream>
#include <winsock2.h>
#include <cmath>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr, clientAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    cout << "UDP Trigonometric Server Running..." << endl;

    char buffer[1024];
    int clientLen = sizeof(clientAddr);

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        recvfrom(serverSocket, buffer, sizeof(buffer), 0,
                 (sockaddr*)&clientAddr, &clientLen);

        string func;
        double angle;

        stringstream ss(buffer);
        ss >> func >> angle;

        double result = 0;
        double rad = angle * M_PI / 180.0;

        if (func == "sin") result = sin(rad);
        else if (func == "cos") result = cos(rad);
        else if (func == "tan") result = tan(rad);
        else result = -9999;

        string reply = to_string(result);

        sendto(serverSocket, reply.c_str(), reply.length(), 0,
               (sockaddr*)&clientAddr, clientLen);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
