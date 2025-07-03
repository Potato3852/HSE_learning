#include <iostream>
#include <vector>
#include<sys/time.h>
#include<initializer_list>
#include<algorithm>
#include<cstring>
using namespace std;

//Theme: "move semantics"
//CopyElision, RVO
//Rvalue References int&&
//Rule of five: constructor copy, constructor move, destructor...

#define GET_TIME(now){\
struct timeval t;\
gettimeofday(&t, NULL);\
now = t.tv_sec+t.tv_usec/1000000.0;\
}

class Vector{
public:
    int getSize() {return size;}
    int getCapacity() { return capacity;}
    void print() {
        for(int i = 0; i < size; i++)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
    }
    Vector() = default;
    Vector(int n, int x) : Vector(n) {
        memset(arr, x, n*sizeof(int));
    }
    Vector(std::initializer_list<int> list) : Vector(list.size()) {
        std::copy(list.begin(), list.end(), arr);
    }
    Vector(const Vector& another) : arr(new int[another.size]), capacity(another.capacity), size(another.size) {
        memcpy(arr, another.arr, size*sizeof(int));
    }

    //Move Copy constructor
    //1. Transfer v to this
    //2. Set v to unitialized but valid state
    Vector(Vector&& v) noexcept : size(move(v.size)), capacity(move(v.capacity)), arr(move(v.arr)), s(move(v.s)) {
        v.arr = nullptr;
        v.size = 0;
        v.capacity = 0;
    }

    //Move assignment operator
    //1. Clean *this
    //2. Transfer v to this
    //3. Set v to unitialized but valid state
    // Vector& operator=(Vector&& v) noexcept {
    //     delete[] arr;
    //     arr = v.arr;
    //     capacity = v.capacity;
    //     size = v.size;
    //     v.arr = nullptr;
    //     v.size = 0;
    //     v.capacity = 0;
    //     return *this;
    // }

    auto operator=(Vector v) {
        Swap(v);
        return *this;
    }

    void Swap(Vector& v) {
        std::swap(arr, v.arr);
        std::swap(capacity, v.capacity);
        std::swap(size, v.size);
    }
     ~Vector(){delete[] arr;}
private:
    Vector(int n) : arr(new int[n]), size(n), capacity(n) {}
    int* arr = nullptr;
    int capacity = 0;
    int size = 0;
    string s;
};

// template<typename T>
// void Swap(T& x, T& y){
//     using rvalue_ref = typename remove_reference<T&>::type &&;
//     T tmp = static_cast<rvalue_ref>(x);
//     x = static_cast<rvalue_ref>(y);
//     y = static_cast<rvalue_ref>(tmp);
// }
// template<typename T>
// void Swap(T& x, T& y) {
//     T tmp = move(x);
// }

int main() {
    vector<Vector> v;
    double start, end;
    GET_TIME(start);


    for(int i = 0; i < 1000; ++i) {
        Vector w(10000,7);
        v.push_back(move(w));
    }


    GET_TIME(end);
    double answer = end - start;
    cout << answer << endl;
}