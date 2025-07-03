#include <iostream>
using namespace std;

template<typename T>
void f(T x, T y) {
    cout << "Not so general\n";
}

template<typename T, typename U>
void f(T x, U y) {
    cout << "General\n";
}

template<>
void f(int x, int y){
    cout << "Specialization\n"; //прошмандовка 
}

int main() {
    
    f(1, 1);
    
}