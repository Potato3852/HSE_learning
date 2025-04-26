#include <iostream>

long long modpow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b % 2 == 1) 
            res = (res * a) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}

struct answer {
    bool isPrime;
    unsigned long long int bad;
    unsigned long long int norm;
};

struct answerMiller {
    bool isPrime;
    unsigned long long int bad;
    unsigned long long int norm1;
    unsigned long long int norm2;
};

answer FermaTest(unsigned long long n) {
    answer res = {true, 0, 0};
    if (n <= 1) return {false, 0, 0};
    if (n <= 3) return {true, 0, n-1};
    if (n == 4) return {false, 0, 0};
    
    for (unsigned long long a = 1; a < n; a++) {
        if (modpow(a, n-1, n) != 1) {
            res.bad++;
            res.isPrime = false;
        } else {
            res.norm++;
        }
    }
    return res;
}

answerMiller MillerRabinTest(unsigned long long n) {
    answerMiller res = {true, 0, 0, 0};
    if (n <= 1) return {false, 0, 0, 0};
    if (n <= 3) return {true, 0, n-1, 0};
    if (n % 2 == 0) return {false, 1, 0, 0};
    
    unsigned long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (unsigned long long a = 1; a < n; a++) {
        unsigned long long x = modpow(a, d, n);
        
        if (x == 1) {
            res.norm1++;
            continue;
        }
        
        bool composite = true;
        for (int r = 0; r < s; r++) {
            if (x == n-1) {
                res.norm2++;
                composite = false;
                break;
            }
            if (r < s-1) {
                x = modpow(x, 2, n);
            }
        }
        
        if (composite) {
            res.bad++;
            res.isPrime = false;
        }
    }
    return res;
}


int main() {
    unsigned long long n;
    std::cin >> n;
    
    auto mr = MillerRabinTest(n);
    std::cout << "Miller-Rabin test: " << (mr.isPrime ? "True" : "False")
              << " " << mr.bad
              << " " << mr.norm1 
              << " " << mr.norm2 << std::endl;

    auto ft = FermaTest(n);
    std::cout << "Fermat test: " << (ft.isPrime ? "True" : "False")
              << " " << ft.bad
              << " " << ft.norm<< std::endl;

    return 0;
}