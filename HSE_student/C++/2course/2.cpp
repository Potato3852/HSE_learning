#include <iostream>

class Robot {
private:
    static int numR;
    
public:
    Robot() {
        numR++;
    }
    Robot(const Robot& other) {
        numR++;
    }
    ~Robot() {
        numR--; 
    }

    int getCount() {return numR;}
};

int Robot::numR = 0;

int main() {
    Robot r1;
    Robot r2 = r1;
    auto r3 = r2;
    std::cout << r1.getCount();
}