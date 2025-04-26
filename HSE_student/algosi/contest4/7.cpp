#include <iostream>
#include <vector>

void eratosthenes_sieve(unsigned long long s, unsigned long long f) {
    std::cout << "Start and finish: " << s << " " << f << std::endl;

    if (f < 2) {
        std::cout << "Primes :\nNo primes" << std::endl;
        return;
    }

    std::vector<bool> isPrime(f + 1, true);
    isPrime[0] = isPrime[1] = false;

    int iteration = 0;
    bool points = false;

    for (unsigned long long p = 2; p <= f; ++p) {
        if (isPrime[p]) {
            iteration++;
            std::vector<unsigned long long> answer;

            for (unsigned long long i = p * p; i <= f; i += p) {
                if (isPrime[i]) {
                    if (i >= s) {
                        answer.push_back(i);
                    }
                    isPrime[i] = false;
                }
            }

            if (!answer.empty()) {
                points = true;
                std::cout << "Iteration : " << iteration << std::endl;
                for (auto num : answer) {
                    std::cout << num << " ";
                }
                std::cout << std::endl;
            }
        }
    }

    std::cout << "Primes :" << std::endl;
    bool searchPrimes = false;
    for (unsigned long long i = s; i <= f; ++i) {
        if (isPrime[i]) {
            std::cout << i << " ";
            searchPrimes = true;
        }
    }

    if (!searchPrimes) {
        std::cout << "No primes";
    }
    std::cout << std::endl;
}

int main() {
    unsigned long long s, f;
    std::cin >> s >> f;
    eratosthenes_sieve(s, f);
    return 0;
}