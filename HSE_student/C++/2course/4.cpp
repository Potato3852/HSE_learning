#include <iostream>

class Linked_list {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };
    
    Node* head;
    Node* tail;

public:
    Linked_list() : head(nullptr), tail(nullptr) {}

    ~Linked_list() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_front(int a) {
        Node* new_node = new Node;
        new_node->value = a;
        new_node->next = head;
        new_node->prev = nullptr;
        
        if (head) {
            head->prev = new_node;
        } else {
            tail = new_node;
        }
        
        head = new_node;
    }

    void push_back(int a) {
        Node* new_node = new Node;
        new_node->value = a;
        new_node->next = nullptr;
        new_node->prev = tail;
        
        if (tail) {
            tail->next = new_node;
        } else {
            head = new_node;
        }
        
        tail = new_node;
    }

    void remove(int a) {
        Node* current = head;
        
        while (current != nullptr && current->value != a) {
            current = current->next;
        }

        if (current == nullptr) {
            return;
        }

        if (current->prev) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }

        if (current->next) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        delete current;
    }
};

int main() {
    
}