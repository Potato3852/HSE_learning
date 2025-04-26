#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Hash_Table {
private:
    struct node {
        std::string value;
        std::string key;
        node* next;
    };

    int size;
    std::vector<node*> table;

public:
    Hash_Table(int initial_size = 101) : size(initial_size) {
        table.resize(size);
    }

    ~Hash_Table() {
        clear();
    }

    void clear() {
        for (auto& entry : table) {
            node* current = entry;
            while (current != nullptr) {
                node* temp = current;
                current = current->next;
                delete temp;
            }
            entry = nullptr;
        }
    }

    void setNode(node* node, std::string value, std::string key) {
        node->key = key;
        node->value = value;
        node->next = nullptr;
    }

    void resize(int newSize) {
        if (newSize <= size) {
            return;
        }

        std::vector<node*> old_table = std::move(table);
        size = newSize;
        table.resize(size);

        for (auto& entry : old_table) {
            node* current = entry;
            while (current != nullptr) {
                put(current->key, current->value);
                node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    int hashFunction(std::string key) {
        int hash = 0;
        for (char ch : key) {
            hash += static_cast<unsigned char>(ch);
        }
        return hash % size;
    }

    void put(std::string key, std::string value) {
        int index = hashFunction(key);
        node* new_node = new node;
        setNode(new_node, value, key);

        if (table[index] == nullptr) {
            table[index] = new_node;
        } else {
            node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    std::string find(std::string key) {
        int index = hashFunction(key);
        node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        return "";
    }

    bool del(std::string key) {
        int index = hashFunction(key);
        node* current = table[index];
        node* previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) {
                    table[index] = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }

        return false;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            node* current = table[i];
            while (current != nullptr) {
                std::cout << "Key: " << current->key << ", Value: " << current->value << std::endl;
                current = current->next;
            }
        }
    }
};

int main() {
    Hash_Table hash_table;
    
    return 0;
}