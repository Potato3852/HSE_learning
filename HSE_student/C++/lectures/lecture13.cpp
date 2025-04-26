#include <iostream>
#include <string>

template<typename T>
T min(T x, T y) {
    return x > y ? y : x;
}

int main() {
    int (*pf1)(int, int) = &min;
    double (*pf2)(double, double) = &min;
    std::string (*pf3)(std::string, std::string) = &min;

    std::cout << reinterpret_cast<void*>(pf1) << std::endl;
    std::cout << reinterpret_cast<void*>(pf2) << std::endl;
    std::cout << reinterpret_cast<void*>(pf3) << std::endl;
}