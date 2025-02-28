#include <iostream>

/*
const - неизменяемые данные
mutable - позволяет изменять неизменяемое
static - существует в единственном экземпляре, вне зависимости от того сколько полей создано и созданы ли вообще
explicit - 
friend - 
*/

class Singleton {
private:
    Singleton(){}
    Singleton(const Singleton&) = delete;
    static Singleton* ptr;
    Singleton operator=(const Singleton&) = delete;
public:
    static Singleton* getObj() {
        if(ptr == nullptr) {
            ptr = new Singleton();
        }
        return ptr;
    }
};
Singleton* ptr = nullptr;

int main() {
    Singleton* ptr = Singleton::getObj();
}