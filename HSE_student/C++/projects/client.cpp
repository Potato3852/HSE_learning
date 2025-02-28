#include <iostream>
#include <WinSock2.h>
#include <string>
#include <thread>
#include <cstdlib>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(default: 4996)

SOCKET connection;
std::atomic<bool> isRunning(true);

// Функция для обработки входящих сообщений от сервера
void ClientHandler()
{
    int login_size, message_size;
    std::string login, message;

    // Получаем логин от сервера
    recv(connection, (char*)&login_size, sizeof(int), NULL);
    login.resize(login_size);
    recv(connection, (char*)login.data(), login_size, NULL);
    std::cout << login << " joined the chat." << std::endl;

    while (isRunning)
    {
        // Получаем логин и сообщение от сервера
        if (recv(connection, (char*)&login_size, sizeof(int), NULL) == SOCKET_ERROR) break;
        login.resize(login_size);
        recv(connection, (char*)&login, login_size, NULL);

        if (recv(connection, (char*)&message_size, sizeof(int), NULL) == SOCKET_ERROR) break;
        message.resize(message_size);
        recv(connection, (char*)message.data(), message_size, NULL);

        std::cout << login << ": " << message << std::endl;
    }

    std::cout << "Disconnected from the server." << std::endl;
}

int main()
{
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 2);
    if (WSAStartup(DLLVersion, &wsaData) != 0)
    {
        std::cout << "ERROR initializing Winsock." << std::endl;
        return 1;
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        std::cout << "Failed to connect to the server." << std::endl;
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server!" << std::endl;

    // Запрос логина у пользователя
    std::string login;
    std::cout << "Enter your login: ";
    std::getline(std::cin, login);

    // Отправка логина на сервер
    int login_size = login.length();
    send(connection, (char*)&login_size, sizeof(int), NULL);
    send(connection, login.c_str(), login_size, NULL);

    // Запуск потока для получения сообщений
    std::thread clientThread(ClientHandler);
    std::string message;
    int message_size;
    while (true)
    {
        std::getline(std::cin, message);
        message_size = message.length();
        send(connection, (char*)&message_size, sizeof(int), NULL);
        send(connection, (char*)&message, message_size, NULL);
    }
    
    clientThread.join();  // Ожидаем завершения потока

    closesocket(connection);
    WSACleanup();
    return 0;
}
