#include <iostream>

/*
Public inheritance
Public -> public
Private -> hidden
Protected ->protected

Private inheritance
Public -> private
Private -> hidden
Protected ->private

Protected inheritance
Public -> protected
Private -> hidden
Protected -> protected
*/

struct Base{
    int x;
    //Base() = default;
    Base(int x) : x(x) {}
    void f() {std::cout << 1 << std::endl;}
};

//EBO empty buffer optimization

struct Derived : Base{
    int y;
    Derived(int y) : Base(0), y(y) {}
    void f() {std::cout << 2 << std::endl;}
};

int main() {
    Derived d(2);
    std::cout << sizeof(Base) << std::endl;
    std::cout << sizeof(Derived) << std::endl;
}