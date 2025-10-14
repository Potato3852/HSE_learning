#include <iostream>

template<typename T>
concept Integer = std::integral<T>;

template<Integer T>
bool isPrime(T n) {

    if(n < 2)
        return false;
    for(T i = 2; i*i <= n; ++i)
        if(n % i == 0)
            return false;

    return true;
}

template<Integer T>
T nextPrime(T n) {
    ++n;
    while(!isPrime(n))
        ++n;
    return n;
}

template<Integer T>
void printPrimesInRange(T start, T end) {
    for(T i = start; i <= end; ++i)
        if(isPrime(i)) std::cout << i << " ";
    std::cout << std::endl;
}

int main() {

}