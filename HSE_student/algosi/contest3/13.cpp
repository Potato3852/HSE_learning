#include <iostream>
#include <string>
#include <vector>

class HashTable {
private:
    struct node {
        std::string key;
        std::string value;
        bool occupied;
        bool deleted;

        node() : occupied(false), deleted(false) {}
    };
    std::vector<node> table;
    long long capacity;
    long long q;
    long long p;

    long long alphabet(char c) {
        if (c >= 'a' && c <= 'z') return c - 'a' + 1;
        else if (c >= 'A' && c <= 'Z') return c - 'A' + 1;
        return 0;
    }

    long long hash(const std::string& key) {
        long long h = 0;
        long long power = 1;
        for (size_t i = 0; i < key.length(); ++i) {
            h = (h + alphabet(key[i]) * power) % q;
            power = (power * p) % q;
        }
        return h;
    }

public:
    HashTable(long long size, long long q, long long p) : table(size), q(q), p(p), capacity(size) {}

    void put(std::string key, std::string value) {
        long long original_index = hash(key);
        long long steps = 0;
        bool exists = false;
        long long found_index = -1;

        while (steps < capacity) {
            long long current_index = (original_index + steps) % capacity;
            if (table[current_index].occupied && !table[current_index].deleted) {
                if (table[current_index].key == key) {
                    exists = true;
                    found_index = current_index;
                    break;
                }
            }
            steps++;
        }

        if (exists) {
            table[found_index].value = value;
            std::cout << "key=" << key << " hash=" << original_index 
                      << " operation=PUT result=replaced value=" << value << std::endl;
            return;
        }

        steps = 0;
        while (steps < capacity) {
            long long current_index = (original_index + steps) % capacity;
            if (!table[current_index].occupied || table[current_index].deleted) {
                table[current_index].key = key;
                table[current_index].value = value;
                table[current_index].occupied = true;
                table[current_index].deleted = false;

                if (steps == 0) {
                    std::cout << "key=" << key << " hash=" << original_index 
                              << " operation=PUT result=inserted value=" << value << std::endl;
                } else {
                    std::cout << "key=" << key << " hash=" << original_index 
                              << " operation=PUT result=collision linear_probing=" << current_index 
                              << " value=" << value << std::endl;
                }
                return;
            }
            steps++;
        }

        std::cout << "key=" << key << " hash=" << original_index 
                  << " operation=PUT result=overflow" << std::endl;
    }

    std::string get(std::string key) {
        long long original_index = hash(key);
        long long steps = 0;

        while(steps < capacity) {
            long long current_index = (original_index + steps) % capacity;
            if(table[current_index].occupied && !table[current_index].deleted) {
                if (table[current_index].key == key) {
                    if(steps == 0) {
                        std::cout << "key=" << key << " hash=" << original_index 
                                  << " operation=GET result=found value=" << table[current_index].value << std::endl;
                    } else {
                        std::cout << "key=" << key << " hash=" << original_index 
                                  << " operation=GET result=collision linear_probing=" << current_index 
                                  << " value=" << table[current_index].value << std::endl;
                    }
                    return table[current_index].value;
                }
            }
            else if (!table[current_index].occupied && !table[current_index].deleted) {
                break;
            }
            steps++;
        }

        if (steps > 0) {
            std::cout << "key=" << key << " hash=" << original_index 
                      << " operation=GET result=collision linear_probing=" << (original_index + steps) % capacity 
                      << " value=no_key" << std::endl;
        } else {
            std::cout << "key=" << key << " hash=" << original_index 
                      << " operation=GET result=no_key" << std::endl;
        }
        return "no_key";
    }

    void del(std::string key) {
        long long original_index = hash(key);
        long long steps = 0;

        while(steps < capacity) {
            long long current_index = (original_index + steps) % capacity;
            if(table[current_index].occupied && !table[current_index].deleted) {
                if (table[current_index].key == key) {
                    table[current_index].deleted = true;
                    table[current_index].occupied = false;
                    
                    if (steps == 0) {
                        std::cout << "key=" << key << " hash=" << original_index 
                                  << " operation=DEL result=removed" << std::endl;
                    } else {
                        std::cout << "key=" << key << " hash=" << original_index 
                                  << " operation=DEL result=collision linear_probing=" << current_index 
                                  << " value=removed" << std::endl;
                    }
                    return;
                }
            }
            else if(!table[current_index].occupied && !table[current_index].deleted) {
                break;
            }
            steps++;
        }

        if (steps > 0) {
            std::cout << "key=" << key << " hash=" << original_index 
                      << " operation=DEL result=collision linear_probing=" << (original_index + steps) % capacity 
                      << " value=no_key" << std::endl;
        } else {
            std::cout << "key=" << key << " hash=" << original_index 
                      << " operation=DEL result=no_key" << std::endl;
        }
    }
};

int main() {
    long long q, p, n;
    std::cin >> q >> p >> n;

    HashTable ht(q, q, p);

    for (long long i = 0; i < n; ++i) {
        std::string op, key;
        std::cin >> op >> key;

        if (op == "PUT") {
            std::string value;
            std::cin >> value;
            ht.put(key, value);
        } else if (op == "GET") {
            ht.get(key);
        } else if (op == "DEL") {
            ht.del(key);
        }
    }

    return 0;
}