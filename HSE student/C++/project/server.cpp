#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Подключаем библиотеку Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

class Server {
public:
    bool start();
    void broadcastMessage(const std::string& message);
    void handleClient(SOCKET clientSocket);

    SOCKET listenSocket = INVALID_SOCKET;
    std::vector<SOCKET> clients;
    std::mutex mutex;

private:
    void cleanup() {
        closesocket(listenSocket);
        WSACleanup();
    }
};

bool Server::start() {
    WSADATA wsaData;
    ADDRINFO hints;
    ADDRINFO* addrResult = nullptr;

    // Инициализация библиотеки Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Ошибка инициализации Winsock: " << WSAGetLastError() << std::endl;
        return false;
    }

    // Настройка параметров адреса
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Получение информации об адресе
    if (getaddrinfo(nullptr, "525", &hints, &addrResult) != 0) {
        std::cerr << "Ошибка получения информации об адресе: " << WSAGetLastError() << std::endl;
        cleanup();
        return false;
    }

    // Создание слушающего сокета
    listenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Ошибка создания слушающего сокета: " << WSAGetLastError() << std::endl;
        freeaddrinfo(addrResult);
        cleanup();
        return false;
    }

    // Привязка сокета к адресу
    if (bind(listenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen) == SOCKET_ERROR) {
        std::cerr << "Ошибка привязки сокета: " << WSAGetLastError() << std::endl;
        freeaddrinfo(addrResult);
        cleanup();
        return false;
    }

    freeaddrinfo(addrResult);

    // Начало прослушивания соединений
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Ошибка начала прослушивания: " << WSAGetLastError() << std::endl;
        cleanup();
        return false;
    }

    std::cout << "Сервер запущен. Ожидание подключений..." << std::endl;

    while (true) {
        // Прием входящих соединений
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Ошибка приема подключения: " << WSAGetLastError() << std::endl;
            continue;
        }

        // Добавление нового клиента в список
        std::lock_guard<std::mutex> lock(mutex);
        clients.push_back(clientSocket);

        // Обработка нового клиента в отдельном потоке
        std::thread t(&Server::handleClient, this, clientSocket);
        t.detach();
    }

    return true;
}

void Server::broadcastMessage(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);
    for (const auto& client : clients) {
        if (send(client, message.c_str(), message.size(), 0) == SOCKET_ERROR) {
            std::cerr << "Ошибка отправки сообщения клиенту: " << WSAGetLastError() << std::endl;
            closesocket(client);
        }
    }
}

void Server::handleClient(SOCKET clientSocket) {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    int result;

    while (true) {
        // Чтение данных от клиента
        result = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);
        if (result > 0) {
            buffer[result] = '\0';
            std::cout << "Получено от клиента: " << buffer << std::endl;
            
            // Отправка сообщения всем клиентам
            broadcastMessage(std::string(buffer));
        } else if (result == 0) {
            std::cout << "Соединение закрыто клиентом." << std::endl;
            break;
        } else {
            std::cerr << "Ошибка чтения данных: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    closesocket(clientSocket);
}

int main() {
    Server server;
    if (!server.start()) {
        std::cerr << "Ошибка запуска сервера" << std::endl;
        return 1;
    }

    return 0;
}