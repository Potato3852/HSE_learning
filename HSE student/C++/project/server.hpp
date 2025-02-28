#ifndef SERVER_HPP
#define SERVER_HPP
#define WIN32_LEAN_AND_MEEN

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

class Server {
public:
    bool start();
    
    void broadcastMessage(const std::string& message);

private:
    void handleClient(SOCKET clientSocket);

    SOCKET listenSocket = INVALID_SOCKET;
    std::vector<SOCKET> clients;
    std::mutex mutex;
};

bool Server::start() {
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = NULL;
    SOCKET clientSocket = INVALID_SOCKET;
    SOCKET listenSocket = INVALID_SOCKET;

    int result;

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cout << "WSAStartup failed, result = " << result << std::endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    result = getaddrinfo(NULL, "525", &hints, &addrResult);
    if (result != 0) {
        std::cout << "getaddrinfo failed with error: " << result << std::endl;
        WSACleanup();
        return 1;
    }

    // Создаем слушающий сокет
    listenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        freeaddrinfo(addrResult);
        std::cout << "Failed to create listen socket" << std::endl;
        return false;
    }

    // Привязываем сокет к адресу
    if (bind(listenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen) == SOCKET_ERROR) {
        freeaddrinfo(addrResult);
        closesocket(listenSocket);
        std::cout << "Error to bind" << std::endl;
        return false;
    }

    freeaddrinfo(addrResult);

    // Начинаем слушать соединения
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(listenSocket);
        std::cout << "Failed to start listen" << std::endl;
        return false;
    }

    std::cout << "Server created. Waiting for connections..." << std::endl;

    while (true) { // Цикл для ожидания и обработки соединений
        clientSocket = accept(listenSocket, NULL, NULL); // Ожидаем входящее соединение
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "accept failed with error: " << WSAGetLastError() << std::endl;
            break; // Завершаем программу при ошибке
        }

        // Добавляем нового клиента в список
        std::lock_guard<std::mutex> lock(mutex);
        clients.push_back(clientSocket);

        // Запускаем поток для обработки нового клиента
        std::thread t(&Server::handleClient, this, clientSocket);
        t.detach();
    }

    closesocket(listenSocket); // Закрываем слушающий сокет
    WSACleanup(); // Освобождаем ресурсы WinSock

    return true;
}

void Server::broadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    for (const auto& client : clients) {
        send(client, message.c_str(), message.size(), 0);
    }
}

void Server::handleClient(SOCKET clientSocket) {
    char buffer[512];
    int result;

    while (true) {
        // Получаем данные от клиента
        result = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (result > 0) {
            buffer[result] = '\0';
            std::cout << "Received from client: " << buffer << std::endl;
            
            // Передаём сообщение всем клиентам
            broadcastMessage(std::string(buffer));
        } else if (result == 0) {
            std::cout << "Connection closed by client." << std::endl;
            break;
        } else {
            std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    closesocket(clientSocket); // Закрываем клиентский сокет
}

#endif // SERVER_HPP