#include <iostream>

class Base{
protected:
    int value = 0;
public:
    int getValue(){
        return value;
    }
    Base(){
        std::cout << "Base" << std::endl;
    }
    ~Base(){
        std::cout << "~Base" << std::endl;
    }
};

class Derived : public Base{
private:
    int value = 3;
public:
    void Value(){
        std::cout << Base::value << std::endl;
    }

    Derived(){
        std::cout << "Derived" << std::endl;
    }

    ~Derived(){
        std::cout << "~Derived" << std::endl;
    }
};

int main(){
    Derived d;
    d.Value();
}

//наследование - это метод передачи полей от одного класса к другому, 
//при том исходный класс-родитель, а новый-наследник
//проблема - ромбовидное наследование
//
//
//
//
//