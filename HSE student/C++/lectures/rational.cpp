#include "rational.hpp"
#include <cmath>
#include <iostream>

Rational::Rational() {
    Numerator = 0;
    Denominator = 1;
}

Rational::Rational(int Numerator, int Denominator) {
    if(Denominator == 0) {
        Rational();
        return;
    }
    int GCD = gcd(abs(Numerator), abs(Denominator));
    if(Numerator > 0 && Denominator < 0 || Numerator < 0 && Denominator < 0) {
        Numerator *= -1;
        Denominator *= -1;
    }
    this->Numerator = Numerator / GCD;
    this->Denominator = Denominator / GCD;
    counter++;
}

int Rational::gcd(int x, int y) {
    while(x > 0 && y > 0)
    {
        if(x > y)
            x %= y;
        else y %= x;
    }
    return x + y;
    counter++;
}

void Rational::printRational() {
    std::cout << this->Numerator << "/" << this->Denominator << std::endl;
    counter++;
}

int Rational::counter = 0;