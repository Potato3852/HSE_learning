#include <iostream>
#include <vector>
using namespace std;
//override, final
//pure virtual function

struct base{
    virtual void f() { cout << "Base" << endl;}
    virtual ~base() = default;
};

struct derived : base{
    void f() override { cout << "Derived" << endl;}
    int* p = new int;
    ~derived() {delete p;}
};

struct Shape{
    virtual double Area() = 0;
};

//double Shape::Area(){}

struct Circle : Shape{
    int r = 1;
    virtual double Area() override {
        return 3.14159 * r * r;
    }
};

struct Triangle : Shape{
    int a = 1;
    int h = 2;
    virtual double Area() override {
        return 0.5*a*h;
    }
};

int main() {

    vector<Shape*> figs;
    figs.push_back(new Triangle());
    figs.push_back(new Circle());
    for(auto it : figs) {
        cout << it->Area() << endl;
    }

}