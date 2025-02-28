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
    SOCKET connectSocket = INVALID_SOCKET;
    ADDRINFO* addrResult = NULL;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cerr << "WSAStartup failed, result = " << result << endl;
        return 1;
    }

    // Создание сокета
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // Используем IPv4 или IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP-сокет
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo *resultAddrInfo;
    result = getaddrinfo("localhost", PORT, &hints, &resultAddrInfo);
    if (result != 0) {
        cerr << "getaddrinfo failed with error: " << result << endl;
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

    // Подключение к серверу
    result = connect(connectSocket, resultAddrInfo->ai_addr, (int)resultAddrInfo->ai_addrlen);
    if (result == SOCKET_ERROR) {
        cerr << "Connection failed." << endl;
        closesocket(connectSocket);
        freeaddrinfo(resultAddrInfo);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(resultAddrInfo); // Освобождаем память после использования

    // Основной цикл общения с сервером
    string message;
    do {
        cout << "Enter a message or \"" << CODE_PHRASE << "\" to exit: ";
        getline(cin, message);
        
        if (message == CODE_PHRASE) {
            break;
        }

        // Отправка сообщения серверу
        result = send(connectSocket, message.c_str(), (int)message.length(), 0);
        if (result == SOCKET_ERROR) {
            cerr << "Send failed with error: " << WSAGetLastError() << endl;
            closesocket(connectSocket);
            WSACleanup();
            return 1;
        }

        // Получение ответа от сервера
        char recvBuffer[512];
        result = recv(connectSocket, recvBuffer, 512, 0);
        if (result > 0) {
            recvBuffer[result] = '\0'; // Завершаем строку нулевым символом
            cout << "Received echo: " << recvBuffer << endl;
        } else if (result == 0) {
            cerr << "Server disconnected." << endl;
            break;
        } else {
            cerr << "Recv failed with error: " << WSAGetLastError() << endl;
            break;
        }
    } while (true);

    // Закрытие соединения
    result = shutdown(connectSocket, SD_BOTH);
    if (result == SOCKET_ERROR) {
        cerr << "Shutdown failed with error: " << WSAGetLastError() << endl;
    }
    closesocket(connectSocket);
    WSACleanup();
    return 0;
}