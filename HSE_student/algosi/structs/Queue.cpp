#include <iostream>

class Queue {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* front;
    Node* back; 
    int size;

public:

    Queue() : front(nullptr), back(nullptr), size(0) {}

    ~Queue() {
        while (front != nullptr) {
            Node* temp = front->next;
            delete front;
            front = temp;
        }
    }

    void push(int value) {
        Node* newNode = new Node{value, nullptr};

        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->next = newNode;
            back = newNode;
        }

        ++size;
    }

    int pop() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста");
        }

        int result = front->value;
        Node* oldFront = front;
        front = front->next;
        delete oldFront;

        if (front == nullptr) {
            back = nullptr;
        }

        --size;
        return result;
    }

    bool find(int a) {
        if (isEmpty()) {
            return false;
        }

        Node* temp = front;
        while (temp != nullptr) {
            if (temp->value == a) {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    int peek() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста");
        }

        return front->value;
    }

    void print() {
        Node* temp = front;
        while (temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    
}