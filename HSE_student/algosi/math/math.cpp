#include <iostream>
#include <vector>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, abs(a % b));
}

int extended_gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int temp = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return temp;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return abs(a * b) / gcd(a, b);
}

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

unsigned long long int fast_pow(unsigned long long int a, int n) {
    long long int answer = 1;
    while (n > 0) {
        if (n % 2 == 1)
            answer *= a;
        a *= a;
        n /= 2;
    }
    return answer;
}

int mod_inverse(int a, int m) {
    int x, y;
    int g = extended_gcd(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

// Китайская теорема об остатках
int crt(const std::vector<int>& a, const std::vector<int>& m) {
    int n = a.size();
    int result = a[0];
    int current_mod = m[0];
    
    for (int i = 1; i < n; ++i) {
        int x, y;
        int gcd = extended_gcd(current_mod, m[i], x, y);
        if ((a[i] - result) % gcd != 0) return -1; // нет решения
        
        int lcm = current_mod / gcd * m[i];
        int temp = (a[i] - result) / gcd * x % (m[i] / gcd);
        result = (result + temp * current_mod) % lcm;
        current_mod = lcm;
    }
    
    return (result % current_mod + current_mod) % current_mod;
}

// int main(int argc, char* argv[]) {
//     int a = std::atoi(argv[1]);
//     int b = std::atoi(argv[2]);

//     std::cout << "GCD: " << gcd(a, b) << std::endl;
//     std::cout << "LCM: " << lcm(a, b) << std::endl;

//     int x, y;
//     int d = extended_gcd(a, b, x, y);
//     std::cout << "Bezout coefficients (x, y): " << x << ", " << y << std::endl;
//     std::cout << "Check: " << a << "*" << x << " + " << b << "*" << y << " = " << d << std::endl;

//     std::cout << a << "^" << b << " = " << fast_pow(a, b) << std::endl;

//     return 0;
// }