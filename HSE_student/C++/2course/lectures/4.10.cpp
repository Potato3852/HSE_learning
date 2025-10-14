#include <iostream>

template<typename T>
class List{
    class Node{
        Node* next, *prev;
        T* payload;
    };
public:
    void add(T payload) {

    }
};

class A{

};

int main(){
    List<int>* intList = new List<int>();
    intList->add(10);
    intList->add(20);

    List<A*>* objList = new List<A* >();
    objList->add(new A());
    objList->add(new A());
}

//templates
//
//
//
//
//
//