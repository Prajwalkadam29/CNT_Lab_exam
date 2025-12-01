#include <iostream>
#include <fstream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET serverSocket, clientSocket;
    char buffer[1024];

    // 1. Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Prepare server address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6000);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // 4. Listen
    listen(serverSocket, 1);
    cout << "File Server waiting..." << endl;

    // 5. Accept connection
    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

    // 6. Receive filename
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);
    string filename = buffer;

    cout << "Client requested file: " << filename << endl;

    ifstream file(filename, ios::binary);
    if (!file) {
        string msg = "NOTFOUND";
        send(clientSocket, msg.c_str(), msg.length(), 0);
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }

    // File found
    string msg = "FOUND";
    send(clientSocket, msg.c_str(), msg.length(), 0);

    // Send file data
    while (!file.eof()) {
        file.read(buffer, sizeof(buffer));
        send(clientSocket, buffer, file.gcount(), 0);
    }

    cout << "File sent successfully!" << endl;

    file.close();
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
