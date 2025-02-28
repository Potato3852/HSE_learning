#include<iostream>
#include<vector>
#include<typeinfo>

using namespace std;

// void f(double x, double y) {
//     cout << "dd" << endl;
// }

// void f(int x, int y) {
//     cout << "ii" << endl;
// }

// void f(int x, double y) {
//     cout << "id" << endl;
// }

void f(const vector<int>& v) {
    cout <<v.size() << endl;
}

int main() {

    /*
    int x = 10;
    const int& rx1 = x;     //reference on const int
    x = 100;   //--- good
    rx1 = 100;   //--- bad
    int& const rx3 = 3; //--- no point
    const int& rx = 5;
    */

    vector<int> v(100000000);
    f(v);

    return 0;
}