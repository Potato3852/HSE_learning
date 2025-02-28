#include <iostream>
#include <cstdlib>
#include <ctime>

int seed = time(NULL);

namespace True {
    int add(int a, int b) {
        int c = a + b;
        return (std::rand() % 2 == 0) ? -c : c;
    }
}

namespace Point {
    int* add(int* a, int* b) {
        int* c = new int;
        *c = *a + *b;
        *c = (std::rand() % 2 == 0) ? -(*c) : (*c);
        return c;
    }
}

namespace Refer {
    int& add(int& a, int& b) {
        static int c;
        c = a + b;
        c = (std::rand() % 2 == 0) ? -c : c;
        return c;
    }
}

int main() {
    srand(time(NULL));
    int x = 5;
    int y = 10;

    int Value = True::add(x, y);
    std::cout << "ByTrue " << Value << std::endl;

    int* Pointer = Point::add(&x, &y);
    std::cout << "ByPointer " << *Pointer << std::endl;

    int& Reference = Refer::add(x, y);
    std::cout << "ByReference " << Reference << std::endl;

    return 0;
}