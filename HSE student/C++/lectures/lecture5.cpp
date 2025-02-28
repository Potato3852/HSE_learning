#include<iostream>
#include"vector.hpp"

int main() {
    Vector v1 = {1, 2, 3};
    Vector v2{2, 3, 4, 5};
    Vector v3 = {4, 5, 6};
    v1 = v1;
    v2.print();
    v3.print();
    v1.print();
}