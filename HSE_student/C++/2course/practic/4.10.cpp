#include <iostream>
#include <stdexcept>

template<typename T>
class SmartPointer {
private:
    T* ptr;
    int* count;
public:
    SmartPointer(T* p = nullptr) : ptr(p) { count = new int(1); }
    ~SmartPointer() {
        delete ptr;
        delete count;
    }
     SmartPointer(const SmartPointer& other) {
        ptr = other.ptr;
        count = other.count;
        (*count)++;
    }

    SmartPointer& operator=(const SmartPointer& other) {
        if(this != &other) {
            ptr = other.ptr;
            count = other.count;
            (*count)++;
        }
        return *this;
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};

int main(){

}