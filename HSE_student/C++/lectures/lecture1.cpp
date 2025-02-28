#include<iostream>
using namespace std;
//using std::cout, std::cin;       использовать сокращение только для этих двух функций
//using lli = long long int;       typedef in c++

namespace N {
    int x = 100;
};

int x = 70;

void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

int& f(int& x)
{
    return ++x;
}

int main() {
    
    int x = 1;
    int* p = &x;
    int*& rp = p;
    int a[10];
    int(&ra)[10] = a;
    int& (&rf)(int&) = f;

}