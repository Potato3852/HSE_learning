#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, abs(a % b));
}

long long extended_gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long temp = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return temp;
}

long long mod_inverse(long long a, long long m) {
    long long x, y;
    long long g = extended_gcd(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

long long kostil(long long a, long long b, long long mod) {
    long long res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1)
            res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}

long long modpow(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1)
            res = kostil(res, a, mod);
        a = kostil(a, a, mod);
        b /= 2;
    }
    return res;
}

int main() {
    long long p, q, e_start;
    std::cin >> p >> q >> e_start;
    std::string str;
    std::cin >> str;

    long long n = p * q;
    long long k = (p - 1) * (q - 1);
    long long e = e_start;
    while (e < k) {
        if (gcd(e, k) == 1) {
            break;
        }
        e++;
    }

    long long d = mod_inverse(e, k);

    std::cout << "Private: " << d << " " << n << std::endl;
    std::cout << "Public: " << e << " " << n << std::endl;
    std::cout << "Initial bytes:";
    for(unsigned char c : str) { std::cout << " " << (long long)c; }
    std::cout << "\nEncrypted bytes:";

    long long m = 0;
    for (unsigned char c : str) {
        m = (m << 8) | c;
    }

    unsigned long long encrypted = modpow(m, e, n);

    std::vector<unsigned char> bytes;
    if (encrypted == 0) {
        bytes.push_back(0);
    } else {
        while (encrypted > 0) {
            bytes.push_back(encrypted % 256);
            encrypted /= 256;
        }
        reverse(bytes.begin(), bytes.end());
    }

    for (auto b : bytes) {
        std::cout << " " << (unsigned long long)b;
    }

    return 0;
}