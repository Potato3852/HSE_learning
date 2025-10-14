//опять шаблоны
//
#include<iostream>

void a(auto* temp){
    std::cout << *temp;
};

int main(){
    int* b;
    a(b);
}