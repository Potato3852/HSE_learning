#include <iostream>

class Singleton {
private:
    static Singleton* pat;

    Singleton() {}
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
public:
    static Singleton* create() {
        if (pat == nullptr) {
            pat = new Singleton();
        }
        return pat;
    }
};

Singleton* Singleton::pat = nullptr;

int main() {

}