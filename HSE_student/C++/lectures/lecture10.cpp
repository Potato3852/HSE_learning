#include <iostream>
#include <string>
#include <vector>

struct Exception {
    Exception() {}
    Exception(const Exception&) {std::cout << "copy" << std::endl;}
    ~Exception() {std::cout <<"destr" << std::endl;}
};

// int divide(int x, int y) {
//     //Exception e("Division by 0");
//     if(y==0)
//         throw Exception("Division by 0"); //copy elision
//     return x / y;
// }

void f() {
    throw 1;
}

// void g() {
//     try {
//         f();
//     } catch(Exception& e) {
//         std::cout << "cought" << std::endl;
//         throw;
//     }
// }

int main() {
    try {
        f();
    } catch(long e) {
        std::cout << "cought in main" << std::endl;
    } catch(long long e) {
        std::cout << "cought in main" << std::endl;
    }
} 