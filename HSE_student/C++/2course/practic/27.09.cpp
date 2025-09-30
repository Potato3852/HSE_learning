// #include <iostream>
// #include <vector>

// using namespace std;

// class Shape {
// public:
//     virtual void draw() { cout << "Drawing" << endl; }
//     virtual ~Shape() = default;
// };

// class Circle : public Shape {
// public:
//     Circle() {}
//     void draw() override { cout << "Drawing a circle" << endl; }
//     void setRadius() {}
// };

// class Rectangle : public Shape {
// public:
//     Rectangle() {}
    
//     void draw() override {
//         cout << "Drawing a rectangle " << endl;
//     }
// };

// int main() {
//     std::vector<Shape*> shapes;
//     shapes.push_back(new Circle);
//     shapes.push_back(new Rectangle);
//     shapes.push_back(new Circle);
//     for(int i = 0; i < shapes.size(); ++i) {
//         Circle* cPtr = dynamic_cast<Circle*>(shapes[i]);
//             if(cPtr!=nullptr){
//             cPtr->setRadius();
//         }
//         shapes[i]->draw();
//     }
// }

#include <iostream>

using namespace std;

class Base{
private:
    virtual void hidden() {}
};

class Derived : public Base{
};

class DerivedWithVirtual : public Base{
public:
    virtual void show() {}
};

int main() {
    Base* base1 = new Derived();
    Base* base2 = new DerivedWithVirtual();
    
    Derived* derived1 = dynamic_cast<Derived*>(base1);
    std::cout << (derived1 ? "SUCCESS" : "FAILED") << std::endl;
    DerivedWithVirtual* derived2 = dynamic_cast<DerivedWithVirtual*>(base2);
    std::cout << (derived2 ? "SUCCESS" : "FAILED") << std::endl;

}