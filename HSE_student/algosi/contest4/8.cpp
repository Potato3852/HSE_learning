#include <iostream>
#include <vector>

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

void factorize(unsigned long long n) {
    if (n == 1) {
        std::cout << "1" << std::endl;
        return;
    }
    
    std::vector<bool> is_prime = sieve_of_eratosthenes(n);
    bool first = true;
    
    for (unsigned long long p = 2; p <= n; ++p) {
        if (is_prime[p]) {
            while (n % p == 0) {
                if (!first) {
                    std::cout << " ";
                }
                std::cout << p;
                n /= p;
                first = false;
            }
        }
        if (n == 1) break;
    }
    
    std::cout << std::endl;
}

int main() {
    unsigned long long n;
    std::cin >> n;
    factorize(n);
    return 0;
}