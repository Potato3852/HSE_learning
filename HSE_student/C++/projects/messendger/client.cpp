#define WIN32_LEAN_AND_MEAN
#define CODE_PHRASE "EXIT"

#include<iostream>
#include<windows.h>
#include<winsock2.h>
#include<ws2tcpip.h>

using namespace std;

int main() {

    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = NULL;
    SOCKET connectSocket = INVALID_SOCKET;

    const char* sendBuffer = "Hello from client";

    char recvBuffer[512];

    int result;

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != 0 ) {
        cout << "WSAStartup failed, result = " << result << endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    result = getaddrinfo("localhost", "525", &hints, &addrResult);
    if(result) {
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    connectSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if(connectSocket == INVALID_SOCKET) {
        cout << "Socket creation failed " <<endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = connect(connectSocket, addrResult->ai_addr, addrResult->ai_addrlen);
    if(result == SOCKET_ERROR) {
        cout << "enable connect to server" << endl;
        closesocket(connectSocket);
        connectSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = send(connectSocket, sendBuffer, (int)strlen(sendBuffer), 0);
    if(result == SOCKET_ERROR) {
        cout << "send failed, error: " << result << endl;
        closesocket(connectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    cout << "Bytes: " << result << endl;

    do {
        ZeroMemory(recvBuffer, 512);
        result = recv(connectSocket, recvBuffer, 512, 0);
        if(result > 0) {
            cout << "received: " << result << endl;
            cout << "received Data: " << recvBuffer << endl;
        } else if(result == 0) {
            cout << "connection closed" << endl;
        } else {
            cout << "recv failed with error" << endl;
        }
    } while(result > 0);

    result = shutdown(connectSocket, SD_SEND);
    if(result == SOCKET_ERROR) {
        cout << "Shutdown error " << result << endl;
        closesocket(connectSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(connectSocket);
    freeaddrinfo(addrResult);
    WSACleanup();
    return 0;
}