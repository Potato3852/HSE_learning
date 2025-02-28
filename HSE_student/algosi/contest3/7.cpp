#include <iostream>

class Stack {
private:
    struct node {
        int value;
        node* prev;
    };
    node* head;
    node* max;

public:
    Stack() : head(nullptr), max(nullptr) {};

    void push(int value) {
        node* newNode = new node{value, head};
        head = newNode;

        if (max == nullptr or value >= max->value) {
            node* maxNode = new node{value, max};
            max = maxNode;
        }
    }

    int pop() {
        int result = head->value;
        node* oldHead = head;
        head = head->prev;
        delete oldHead;

        if (max != nullptr && result == max->value) {
            node* maxTemp = max;
            max = max->prev;
            delete maxTemp;
        }

        return result;
    }

    void getMax() {
        std::cout << max->value <<std::endl;
    }

};

int main() {
    Stack stack;
    int n, value;
    std::string command;
    std::cin >> n;

    for(int i = 0; i < n; i++) {
        std::cin >> command;
        if(command == "push") {
            std::cin >> value;
            stack.push(value);
        } else if(command == "pop") {
            stack.pop();
        } else if(command == "max") {
            stack.getMax();
        }
    }
}