#include <iostream>
#include <iomanip>
#include <functional>
#include <vector>
//method of chetirepecia

// double Trap(double a, double b, int n, std::function<double(double)> f) {
//     double res = 0.5*(f(a) + f(b));
//     double h = (b-a)/n;
//     for(int i = 0; i < n; i++) {
//         double x = a + i * h;
//         res += f(x);
//     }
//     res *= h;
//     return res;
// }

// int main() {

//     std::cout << std::fixed << std::setprecision(2);
//     std::cout << Trap(0, 3, 10, [](double x){return x*x;}) << std::endl;
//     std::cout << Trap(0, 3, 10, [](double x){return x;}) << std::endl;
//     return 0;
// }

int main() {

    std::vector<int> v = {1, 2, 3, 4};
    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    v.push_back(100);
    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    v.pop_back();
    v.shrink_to_fit();
    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    v.resize(10, 1000);
    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    v.reserve(11);
    std::cout << v.size() << ' ' << v.capacity() << std::endl;
    
    return 0;
}