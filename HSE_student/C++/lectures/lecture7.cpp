#include <iostream>

// class C {
//     int x = 1;
//     int y = 2;
//     friend class B;
//     friend void f(const C& c);
// };

// void f(const C& c) {std::cout << c.x << std::endl;}

// class B{
//     void f(){};
// };

struct Complex{
    double re = 0.0;
    double im = 0.0;
    Complex() = default;
    Complex(double re): re(re) {}
    Complex(double re, double im) : re(re), im(im) {}
    Complex& operator+=(const Complex& c) {
        //*this = *this + c;  lame
        re += c.re;
        im = c.im;
        return *this;
    }
    friend Complex operator+(const Complex& c1, const Complex& c2);
    std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.re << ' ' << c.im;
        return os;
    }
};

Complex operator+(const Complex& c1, const Complex& c2){  
    return Complex(c1.re + c2.re, c1.im + c2.im); //lame
}


struct S {
    int x = 1;
    S& operator++(){++x; return *this;}
    S operator++(int) {
        S copy = *this;
        ++x;
        return copy;
    }
};

int main() {
    Complex c1(1, 2);
    S s;
    ++s;
    s++;

    std::cout << s.x <<std::endl;
    return 0;
}