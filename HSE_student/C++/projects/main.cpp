#include "server.hpp"
#include "client.hpp"

int main() {
    // Инициализация библиотеки WinSock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Ошибка инициализации WinSock" << std::endl;
        return 1;
    }

    // Запуск сервера
    Server server;
    if (!server.start()) {
        std::cerr << "Ошибка запуска сервера" << std::endl;
        return 1;
    }

    // Запуск клиентов
    Client client1("127.0.0.1", 8080);
    Client client2("127.0.0.1", 8080);

    if (!client1.connect()) {
        std::cerr << "Ошибка подключения клиента 1" << std::endl;
        return 1;
    }

    if (!client2.connect()) {
        std::cerr << "Ошибка подключения клиента 2" << std::endl;
        return 1;
    }

    client1.run();
    client2.run();

    // Завершение работы с библиотекой WinSock
    WSACleanup();

    return 0;
}