#include <iostream>
#include <string>
#include <vector>

class Hash_Table {
private:
    struct node {
        std::string key;
        node* next;
    };

    int size;
    std::vector<node*> table;

public:
    Hash_Table(int initial_size) : size(initial_size) {
        table.resize(size);
    }

    int hashFunction(const std::string& key, int m) {
        long long p = 1000000007;
        long long x = 263;
        long long temp = 1;
        long long hash = 0;
        
        for(char a : key) {
            hash = (hash + (a * temp) % p) % p;

            temp = (temp * x) % p;
        }

        return hash % m;
    }

    void add(std::string key) {
        int index = hashFunction(key, size);
        node* current = table[index];

        while(current!= nullptr) {
            if(current->key == key) { return; }

            current = current->next;
        }

        node* newNode = new node{key, table[index]};
        table[index] = newNode;
    }

    bool del(std::string key) {
        int index = hashFunction(key, size);
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

    std::string find(const std::string& key) {
        int index = hashFunction(key, size);
        node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return "yes";
            }
            current = current->next;
        }

        return "no";
    }

    std::string check(int index) {
        node* current = table[index];
        std::string temp;

        while(current != nullptr) {
            temp += current->key + " ";
            current = current->next;
        }

        if(!temp.empty()) {
            temp.pop_back();
        }

        return temp;
    }
    
};

int main() {
    int m,n;
    std::cin >> m;
    std::cin >> n;

    Hash_Table table(m);

    std::string command;
    for(int i = 0; i < n; i++) {
        std::cin >> command;
        if(command == "add") {
            std::string key;
            std::cin >> key;
            table.add(key);
        } else if (command == "find") {
            std::string key;
            std::cin >> key;
            std::cout << table.find(key) << std::endl;
        } else if (command == "del") {
            std::string key;
            std::cin >> key;
            table.del(key);
        } else if (command == "check") {
            int key;
            std::cin >> key;
            std::cout << table.check(key) << std::endl;
        }
    }

    return 0;
}