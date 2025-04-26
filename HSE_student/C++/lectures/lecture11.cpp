#include <iostream>

struct Granny{
    int g = 0;
};

struct Mom : virtual Granny{
    int m = 1;
};

struct Dad : virtual Granny{
    int d = 2;
};

struct Son : Mom, Dad{
    int s = 3;
};

/*
Issues:
1. diamond-shaped inheritance -- just use using namespace
2. inaccessible base class -- when Son : mom, granny BUT mom : granny
3. pointer shift 
*/

int main() {
    Son son;
    std::cout << son.g << std::endl;
    std::cout << sizeof(son) << std::endl;
}