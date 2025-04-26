#include <iostream>
#include <vector>
#include <algorithm> //only for std::count
#include "math.cpp"

//----------------------------
bool NaiveIsPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

bool OptimizedIsPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i*i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) 
            return false;
    }
    return true;
}
//-----------------------------
std::vector<bool> sieve_of_eratosthenes(unsigned long long n) {
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (unsigned long long i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (unsigned long long j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

std::vector<unsigned long long> result_sieve(unsigned long long n) {
    std::vector<bool> array = sieve_of_eratosthenes(n);
    std::vector<unsigned long long> result;

    for(unsigned long long i = 0; i < n; ++i) {
        if(array[i]){
            result.push_back(i);
        }
    }
    return result;
}

int prime_distribution_function(unsigned long long n) {
    std::vector<bool> primes = sieve_of_eratosthenes(n);
    return std::count(primes.begin(), primes.end(), true);
}

bool FermaTest(unsigned long long n, int k = 5) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;
    
    while(k > 0){
        int a = 2 + rand() % (n-4);
        if (modpow(a, n-1, n) != 1) return false;
        k--;
    }
    return true;
}

// Тест Миллера-Рабина (более надежный вероятностный тест)
bool MillerRabinTest(unsigned long long n) {

    int iterations = 5;
    if (n != 2 && n % 2 == 0) return false;
    if (n < 2) return false;
    
    unsigned long long d = n - 1;
    while (d % 2 == 0) 
        d /= 2;
    
    for (int i = 0; i < iterations; i++) {
        unsigned long long a = 2 + rand() % (n - 4);
        unsigned long long x = modpow(a, d, n);
        
        if (x == 1 || x == n - 1)
            continue;
        
        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;
            
            if (x == 1) 
                return false;
            if (x == n - 1) 
                break;
        }
        
        if (x != n - 1)
            return false;
    }
    return true;
}

//Ультра комба для контеста
bool IsPrime(unsigned long long n) {
    // Маленькие числа
    if (n <= 1) return false;
    if (n <= 3) return true;
    
    // Чётные числа и кратные 3
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    // Проверяем несколько маленьких простых делителей для скорости
    const int small_primes[] = {5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int p : small_primes) {
        if (n % p == 0) return n == p;
    }
    
    // Тест Миллера-Рабина для надежности
    return MillerRabinTest(n);
}

int main() {
    int n = 31;
    std::cout << FermaTest(n);
}