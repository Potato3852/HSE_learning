/*Специфические методы класса
Конструкторы - метод, вызываемый при создании класса
Деструктор - метод класса, вызывваемый при его разрушении
Внутренний класс - вложенный класс, имеющий область действия, ограниченную внешний классом
Дружественный элемент - элемент являющийся другим объектом, но имеющий доступ к приватным полям певого объекта
*/

#include <iostream>
#include <cstring>
#include <string>

class String{
private:
    char* value;

public:
    String(const char* temp = nullptr) {
        value = new char[strlen(temp) + 1];
        strcpy(value, temp);
    }

    String(const String& other) {
        if (other.value) {
            value = new char[strlen(other.value) + 1];
            strcpy(value, other.value);
        } else {
            value = nullptr;
        }
    }
    ~String() { delete [] value; }
};

class Tracer{
private:
    std::string f_name;

public:
    Tracer(const std::string f_name) : f_name(f_name) {
        std::cout << "Enter " << f_name << "\n";
    }

    ~Tracer() {
        std::cout << "Leave " << f_name << "\n";
    }
};

void test() {
    Tracer tracer("test");
    std::cout << "Test" << std::endl;
}

class Matrix{
private:
    int** data;
    int n, m;
public:
    Matrix(int n, int m) : n(n), m(m) {
        data = new int*[n];
        for(int i = 0; i < n; ++i) {
            data[i] = new int[m];
        }
    }

    ~Matrix() {
        for(int i = 0; i < n; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
};

//========================
class Application {
public:
    void logEvent(int n);
};

class Logger {
private:
    static int logCount;
    friend void Application::logEvent(int n);
public:
    static int getCount() { return logCount; }
};

int Logger::logCount = 0;

void Application::logEvent(int n) {
    Logger::logCount += n;
}

int main() {
    Application app;
    
    std::cout << "Initial count: " << Logger::getCount() << std::endl;
    
    app.logEvent(5);
    std::cout << "After adding 5: " << Logger::getCount() << std::endl;
    
    app.logEvent(10);
    std::cout << "After adding 10: " << Logger::getCount() << std::endl;
    
    return 0;
}