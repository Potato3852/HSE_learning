#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#define PORT "525"
#define CODE_PHRASE "EXIT"

using namespace std;

int main() {
    // Инициализация WinSock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cerr << "WSAStartup failed, result = " << result << endl;
        return 1;
    }

    // Создание сокета
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;      // Используем только IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP-сокет
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;     // Для привязки к локальному адресу

    struct addrinfo *resultAddrInfo;
    result = getaddrinfo(NULL, PORT, &hints, &resultAddrInfo);
    if (result != 0) {
        cerr << "getaddrinfo failed with error: " << result << endl;
        WSACleanup();
        return 1;
    }

    SOCKET listenSocket = socket(resultAddrInfo->ai_family, resultAddrInfo->ai_socktype, resultAddrInfo->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed." << endl;
        freeaddrinfo(resultAddrInfo);
        WSACleanup();
        return 1;
    }

    // Привязываем сокет к порту
    result = bind(listenSocket, resultAddrInfo->ai_addr, (int)resultAddrInfo->ai_addrlen);
    if (result == SOCKET_ERROR) {
        cerr << "Binding failed with error: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        freeaddrinfo(resultAddrInfo);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(resultAddrInfo); // Освобождаем память после использования

    // Начинаем прослушивание порта
    result = listen(listenSocket, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        cerr << "Listen failed with error: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Ожидаем подключения клиента
    SOCKET clientSocket = accept(listenSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Accept failed with error: " << WSAGetLastError() << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    closesocket(listenSocket); // Больше не нужен слушающий сокет

    // Основной цикл обработки сообщений от клиента
    char recvBuffer[512];
    do {
        ZeroMemory(recvBuffer, 512);
        result = recv(clientSocket, recvBuffer, 512, 0);
        if (result > 0) {
            recvBuffer[result] = '\0'; // Завершаем строку нулевым символом

            // Проверяем, является ли полученное сообщение командой завершения
            if (strcmp(recvBuffer, CODE_PHRASE) == 0) {
                cout << "Received termination command. Shutting down." << endl;
                break;
            }

            cout << "Received: " << recvBuffer << endl;

            // Отправляем обратно клиенту то же самое сообщение (эхо)
            result = send(clientSocket, recvBuffer, (int)strlen(recvBuffer), 0);
            if (result == SOCKET_ERROR) {
                cerr << "Send failed with error: " << WSAGetLastError() << endl;
                break;
            }
        } else if (result == 0) {
            cerr << "Client disconnected." << endl;
            break;
        } else {
            cerr << "Recv failed with error: " << WSAGetLastError() << endl;
            break;
        }
    } while (true);

    // Закрываем соединение с клиентом
    result = shutdown(clientSocket, SD_BOTH);
    if (result == SOCKET_ERROR) {
        cerr << "Shutdown failed with error: " << WSAGetLastError() << endl;
    }
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}