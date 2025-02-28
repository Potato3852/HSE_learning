#include <iostream>

class Linked_List {
private:
    struct node {
        int value;
        node* next;
    };
    node* head;
    int size;

public:
    Linked_List() : head(nullptr), size(0) {}

    ~Linked_List() {
        node* current = head;
        while (current) {
            node* next = current->next;
            delete current;
            current = next;
        }
    }

    void push_front(int a) {
        node* current = new node;
        current->value = a;
        current->next = head;
        head = current;
        size++;
    }

    void push_back(int a) {
        if (head == nullptr) {
            head = new node;
            head->value = a;
            head->next = nullptr;
            size++;
        } else {
            node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            node* temp = new node;
            temp->value = a;
            temp->next = nullptr;
            current->next = temp;
            size++;
        }
    }

    bool search(int aim) {
        node* current = head;
        while (current != nullptr) {
            if (current->value == aim) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void insert_after(int a, int b) {
        if (!search(a)) {
            std::cout << "Error to insert after \"" << a << "\"" << std::endl
                      << "Element not found!!!" << std::endl;
            return;
        }

        node* current = head;
        while (current != nullptr && current->value != a) {
            current = current->next;
        }

        if (current->next == nullptr) {
            push_back(b);
            return;
        }

        node* temp = new node;
        temp->value = b;
        temp->next = current->next;
        current->next = temp;
        size++;
    }

    void insert_before(int a, int b) {
        if (!search(a)) {
            std::cout << "Error to insert before \"" << a << "\"" << std::endl
                      << "Element not found!!!" << std::endl;
            return;
        }

        node* current = head;
        node* prev = nullptr;

        while (current != nullptr && current->value != a) {
            prev = current;
            current = current->next;
        }

        if (prev == nullptr) {
            push_front(b);
        } else {
            node* temp = new node;
            temp->value = b;
            temp->next = current;
            prev->next = temp;
            size++;
        }
    }

    void remove(int a) {
        if (!search(a)) {
            std::cout << "Error deleting \"" << a << "\"" << std::endl
                      << "Element not found!!!" << std::endl;
            return;
        }

        node* current = head;
        node* prev = nullptr;

        while (current != nullptr && current->value != a) {
            prev = current;
            current = current->next;
        }

        if (current == head) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        size--;
    }

    void remove_head() {
        if (head == nullptr) {
            std::cout << "List is empty! Cannot remove head." << std::endl;
            return;
        }

        node* temp = head;
        head = head->next;
        delete temp;
        size--;

        if (size == 0) {
            head = nullptr;
        }
    }

    void remove_tail() {
        if (head == nullptr) {
            std::cout << "List is empty! Cannot remove tail." << std::endl;
            return;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            size--;
            return;
        }

        node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;
        size--;
    }

    int get_size() {
        return size;
    }

    void print() {
        node* temp = head;

        while (temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    Linked_List list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }
    list.print();
    std::cout << "Size of the list: " << list.get_size() << std::endl;
    list.remove(4);
    list.print();
    std::cout << "Size of the list: " << list.get_size() << std::endl;
    list.remove(0);
    list.print();
    std::cout << "Size of the list: " << list.get_size() << std::endl;
    list.remove(9);
    list.print();
    std::cout << "Size of the list: " << list.get_size() << std::endl;
    list.remove_tail();
    list.print();
    std::cout << "Size of the list: " << list.get_size() << std::endl;
    list.remove_head();
    list.print();

    std::cout << "Size of the list: " << list.get_size() << std::endl;
}