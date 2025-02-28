#include <iostream>
#include <string>
#include <vector>

const int p = 300007;
const int x = 263;

struct Pair {
    std::string first;
    std::string second;
    bool deleted = false;
};

class HashTable {
public:
    int hash(const std::string& s) const {
        long long result = 0;
        long long q = 1;
        for (int i = 0; i < s.size(); ++i) {
            result = (result + s[i] * q) % p;
            q = (q * x) % p;
        }
        return result % m;
    }

    std::vector<Pair> table;
    int m;

    HashTable(int size) : m(size) {
        table.resize(m);
    }

    void add(const std::string& s, const std::string& toPut) {
        int index = hash(s);
        int originalIndex = index; 
        int probeCount = 0;  

        while (!table[index].first.empty() && !table[index].deleted && probeCount < m) {
           
            index = (index + 1) % m;
            probeCount++;
        }

        table[index].first = s;
        table[index].second = toPut;
        table[index].deleted = false;
    }

    void del(const std::string& s) {
        int index = hash(s);
        int originalIndex = index;
        int probeCount = 0;

        while (probeCount < m) {
            if (table[index].first == s && !table[index].deleted) {
                table[index].deleted = true;
                break;
            }
            index = (index + 1) % m;
            probeCount++;
        }

        
    }

    void printNext(const std::string& s) {
        int index = hash(s);
        int originalIndex = index;
        int probeCount = 0;

        while (table[index].first != s && probeCount < m ) {
            index = (index + 1) % m;
            probeCount++;
        }

        if (table[index].first == s && !table[index].deleted) {
            std::string next = table[index].second;
            if (next == "-1") {
                std::cout << "-1" << std::endl;
            }
            else {
                int nextIndex = hash(next);
                while (table[nextIndex].deleted && table[nextIndex].second != "-1") {
                    next = table[nextIndex].second;
                    nextIndex = hash(next);
                }

                if (table[nextIndex].deleted) {
                    std::cout << "-1" << std::endl;
                }
                else {
                    std::cout << table[nextIndex].first << std::endl;
                }
            }
        }
        else {
            int i =( index+1)%m;
            if (table[index].first == table[index].second)

                std::cout << table[i].second << std::endl;
            else
                std::cout << "-1" << std::endl;
        }
    }
    void printTable()
    {
        for (auto& it : table)
            std::cout << it.first << ' ' << it.second << it.deleted << std::endl;
    }
};

int main() {
    int n, q;
    std::cin >> n >> q;
    /*if (n == 0)
        return 0
    if (n == 1)
    {
        std::cout << -1; return 0;
    }*/
    HashTable ht(300007);
    std::vector<std::string> strs(n);
    std::string s;

    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        strs[i] = s;
    }

    for (int i = 0; i < n - 1; ++i) {
        ht.add(strs[i], strs[i + 1]);
    }
    ht.add(strs[n - 1], "-1");

    for (int i = 0; i < q; ++i) {
        int type;
        std::string s;
        std::cin >> type >> s;

        if (type == 1) {
            ht.del(s);
        }
        else if (type == 2) {
            ht.printNext(s);
        }
    }
   // ht.printTable();

    return 0;
}
