#include <iostream>

class Rectangle{
private:
    double width, height;
public:
    Rectangle(double w=0, double h=0) : width(w), height(h) {}

    double area() {return width * height;}
    double perimeter() {return (width + height) * 2;}
};

int main() {
    Rectangle A(2,3);
    std::cout << A.area() << std::endl << A.perimeter();
}