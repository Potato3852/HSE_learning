#include <iostream>

class Stack {
private:
    struct node {
        int value;
        node* prev;
    };
    node* head;
    int size;

public:
    Stack() : head(nullptr), size(0) {};

    ~Stack() {
        while(head != nullptr) {
            node* temp = head->prev;
            delete head;
            head = temp;
        }
    }

    void push(int value) {
        node* newNode = new node{value, head};
        head = newNode;
        ++size;
    }

    int pop() {
        if (isEmpty()) {
            throw std::runtime_error("Стек пуст");
        }
        
        int result = head->value;
        node* oldHead = head;
        head = head->prev;
        delete oldHead;
        --size;
        return result;
    }

    bool find(int a) {
        node* temp = head;
        if(isEmpty()) {
            throw std::runtime_error("Стек пуст");
        } else {
            while(temp != nullptr) {
                if(temp->value == a) {
                    return true;
                }
                temp = temp->prev;
            }
            return false;
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    int top() {
        return head->value;
    }

    void print() {
        node* temp = head;
        while(temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack stack;
    stack.push(1);
    stack.print();
    stack.push(2);
    stack.print();
    stack.push(3);
    stack.print();
    stack.push(4);
    stack.print();
    stack.push(5);
    stack.print();
    stack.pop();
    stack.print();
    stack.pop();
    stack.print();
    std::cout << stack.find(3) << std::endl;
    std::cout << stack.top();
}