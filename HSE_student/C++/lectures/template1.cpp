#include <iostream>
#include <array>
using namespace std;

template<typename T, int N>
class Array{
    T a[N];
};

template<int M, int N, typename Field>
struct Matrix{
    template<int K>
    Matrix<M, K, Field> operator*(Matrix<N, K, Field>){}
};

template<typename Field, int N>
using SquareMatrix = Matrix<N, N, Field>;

template<typename T>
T pi = 3.14159;

template<int N>
struct Fibonacci{
    constexpr static long long value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template<>
struct Fibonacci<1>{ 
    constexpr static long long value = 1;
};

template<>
struct Fibonacci<0>{ 
    constexpr static long long value = 1;
};

template<int N, int K>
struct isPrimeHelper{
    constexpr static bool value = N % K == 0 ? false : isPrimeHelper<N, K-1>::value;
};

template<int N>
struct isPrimeHelper<N, 1>{
    constexpr static bool value = true;
};

template<int N>
struct isPrime{
    constexpr static bool value = isPrimeHelper<N, N-1>::value;
};

template<int N>
constexpr static bool is_prime = isPrime<N>::value;

int main() {

    cout << Fibonacci<5>::value << endl;
    cout << isPrime<113>::value << endl;
    cout << is_prime<7> << endl;
    // int m;
    // cin >> m;
    // constexpr int n = 2;
    // Matrix<2,4, int> a;
    // Matrix<4,1, int> b;
    
}

//нетиповые значения должны быть известны в момент компиляции
//constexpr явно указывает на то, что переменная должна быть известна во время компиляции
//g++ -ftemplate-depth=2025 lecture15.cpp -o main ----- черная магия с флажком, который задает ограничение для создания шаблонов