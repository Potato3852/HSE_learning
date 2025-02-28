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
    SOCKET clientSocket = INVALID_SOCKET;
    SOCKET listenSocket = INVALID_SOCKET;

    const char* sendBuffer = "Hello from server";

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
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL, "525", &hints, &addrResult);
    if(result != 0) {
        cout << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    listenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if(listenSocket == INVALID_SOCKET) {
        cout << "Socket creation failed " <<endl;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = bind(listenSocket, addrResult->ai_addr, addrResult->ai_addrlen);
    if(result == SOCKET_ERROR) {
        cout << "binding socket failed" << endl;
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    result = listen(listenSocket, SOMAXCONN);
    if(result == SOCKET_ERROR) {
        cout << "listening socket failed" << endl;
        closesocket(listenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    clientSocket = accept(listenSocket, NULL, NULL);
    if(clientSocket == INVALID_SOCKET) {
        cout << "accepting socket failed" << endl;
        closesocket(listenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(listenSocket);

    do {
        ZeroMemory(recvBuffer, 512);
        result = recv(clientSocket, recvBuffer, 512,  0);
        if(result > 0) {
            cout << "received: " << result << " bytes" << endl;
            cout << "received Data: " << recvBuffer << endl;

            result = send(clientSocket, sendBuffer, strlen(sendBuffer), 0);
            if(result == SOCKET_ERROR) {
                cout << "failed to send data back" << endl;
                closesocket(clientSocket);
                freeaddrinfo(addrResult);
                WSACleanup();
                return 1;
            }
        } else if(result == 0) {
            cout << "connection closing..." << endl;
        } else {
            cout << "recv failed with error" << endl;
            closesocket(clientSocket);
            freeaddrinfo(addrResult);
            WSACleanup();
            return 1;
        }
    } while(result > 0);

    result = shutdown(clientSocket, SD_SEND);
    if(result == SOCKET_ERROR) {
        cout << "failed to shutdown socket" << endl;
        closesocket(clientSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(clientSocket);
    freeaddrinfo(addrResult);
    WSACleanup();
    return 0;
}