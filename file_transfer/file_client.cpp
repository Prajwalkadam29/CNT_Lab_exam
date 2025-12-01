#include <iostream>
#include <fstream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET clientSocket;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Take filename input
    string filename;
    cout << "Enter filename to download: ";
    cin >> filename;

    // Send filename
    send(clientSocket, filename.c_str(), filename.length(), 0);

    // Response
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    recv(clientSocket, buffer, sizeof(buffer), 0);

    if (string(buffer) == "NOTFOUND") {
        cout << "File not found on server!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }

    // Save file
    ofstream outfile("downloaded_" + filename, ios::binary);

    int bytes;
    while ((bytes = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        outfile.write(buffer, bytes);
    }

    cout << "File downloaded successfully!" << endl;

    outfile.close();
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
