#include <iostream>
#include <vector>
#include <string>
//короче я понял, что список в целом плохая идея делать список была, условие просто запутало
//надо было акцент на операции делать а не на псевдоусловие

int KOSTIL = 300007;
class Hash_table {
private:
    struct node{
        std::string key;
        std::string value;
        node* next;

        node(const std::string& k, const std::string& v) : key(k), value(v), next(nullptr) {}
    };
    std::vector<node*> table;
    int size;
    
    int hash(const std::string& key) {
        const int p = 31;
        int hash_value = 0;
        for (char c : key) {
            hash_value = (hash_value * p + c) % KOSTIL;
        }
        return hash_value;
    }

public:
    Hash_table() : table(KOSTIL, nullptr) {}

    void push(const std::string& key, const std::string& value) {
        int index = hash(key);
        node* temp = new node(key, value);
        temp->next = table[index];
        table[index] = temp;
    }

    std::string get(const std::string& key) {
        int index = hash(key);
        node* current = table[index];
        while(current) {
            if(current->key ==key) {
                return current->value;
            }
            current = current->next;
        }
        return "";
    }

    void remove(const std::string& key) {
        int index = hash(key);
        node* current = table[index];
        node* prev = nullptr;
        
        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
};

int main() {
    int n, q;
    std::cin >> n >> q;
    Hash_table previos;
    Hash_table next;

    std::string current, prev;
    for (int i = 0; i < n; ++i) {
        std::cin >> current;
        
        if (!prev.empty()) {
            next.push(prev, current);
            previos.push(current, prev);
        }
        prev = current;
    }

    for(int i = 0; i < q; i++) {
        int command;
        std::cin >> command;

        if(command == 1) {
            std::string x;
            std::cin >> x;
            
            std::string prev_x = previos.get(x);
            std::string next_x = next.get(x);
            
            if (!prev_x.empty()) 
                next.push(prev_x, next_x);

            if (!next_x.empty()) 
                previos.push(next_x, prev_x);
            
            next.remove(x);
            previos.remove(x);
        } else if (command == 2) {
            std::string x;
            std::cin >> x;

            std::string temp = next.get(x);
            if(temp.empty())
                std::cout << "-1" << std::endl;
            else
                std::cout << temp << std::endl;
        }
    }
}