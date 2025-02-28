#pragma once
#include <iostream>

class Rational {
public:
    Rational();
    Rational(int Numerator, int Denominator);
    int getNum()const{return Numerator;}
    int getDem()const{return Denominator;}
    void printRational();
    static int getCounte() {return counter;}
private:
    int Numerator;
    int Denominator;
    int gcd(int x, int y); 
    static int counter;
};