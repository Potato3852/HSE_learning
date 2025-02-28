#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "crypto.hpp"

class Client {
public:
    Client(const std::string& ip, int port);
    ~Client();
    bool connect();
    void run();
private:
    const std::string ip;
    const int port;
    SOCKET sock = INVALID_SOCKET;
    std::string key;
};

// Реализация конструктора
Client::Client(const std::string& ip, int port)
    : ip(ip), port(port) {}

// Реализация деструктора
Client::~Client() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }
    WSACleanup(); // Завершаем работу с WinSock
}

bool Client::connect() {
    WSADATA wsaData;
    int wsResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (wsResult != 0) {
        std::cerr << "WSAStartup failed with error code " << wsResult << std::endl;
        return false;
    }

    struct addrinfo hints, *result = nullptr, *ptr;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // Указываем конкретный тип адреса IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Получение информации о сервере
    std::string portStr = std::to_string(port); // Преобразуем порт в строку
    if (getaddrinfo(ip.c_str(), portStr.c_str(), &hints, &result) != 0) {
        std::cerr << "Failed to get information about the server." << std::endl;
        WSACleanup();
        return false;
    }

    // Создание сокета и подключение к серверу
    for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
        sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (sock == INVALID_SOCKET) {
            std::cerr << "Socket creation failed with error code " << WSAGetLastError() << std::endl;
            WSACleanup();
            return false;
        }

        if (::connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen) == 0) {
            std::cout << "Successfully connected to the server." << std::endl;
            break;
        } else {
            std::cerr << "Connection attempt failed with error code " << WSAGetLastError() << std::endl;
            closesocket(sock);
            sock = INVALID_SOCKET;
        }
    }

    freeaddrinfo(result); // Освободить память, выделенную под результат getaddrinfo

    if (sock == INVALID_SOCKET) {
        std::cerr << "Unable to connect to the server." << std::endl;
        WSACleanup();
        return false;
    }

    return true;
}

void Client::run() {
    while (true) {
        std::string message;
        std::getline(std::cin, message);

        if (message.empty()) continue;

        // Шифруем сообщение
        std::string encryptedMessage = encrypt(message, key);
        std::cout << "Your message: " << encryptedMessage << std::endl;

        // Отправляем зашифрованное сообщение на сервер
        if (send(sock, encryptedMessage.c_str(), (int)encryptedMessage.length(), 0) == SOCKET_ERROR) {
            std::cerr << "Error sending message: " << WSAGetLastError() << std::endl;
            break;
        }

        // Буфер для чтения данных
        constexpr size_t BUFFER_SIZE = 4096;
        char buffer[BUFFER_SIZE];
        std::string receivedMessage;

        // Чтение данных частями до тех пор, пока не будут получены все данные
        do {
            int bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0);
            if (bytesReceived > 0) {
                receivedMessage.append(buffer, bytesReceived);
            } else if (bytesReceived == 0) {
                std::cerr << "Connection closed by server." << std::endl;
                break;
            } else {
                std::cerr << "Error receiving response: " << WSAGetLastError() << std::endl;
                break;
            }
        } while (receivedMessage.find('\n') == std::string::npos); // Продолжаем чтение до конца строки

        if (!receivedMessage.empty()) {
            std::string decryptedMessage = decrypt(receivedMessage, key);
            std::cout << "Decrypted message: " << decryptedMessage << std::endl;
        }

        closesocket(sock);
        WSACleanup();
    }

    closesocket(sock);
    WSACleanup();
}

#endif // CLIENT_HPP