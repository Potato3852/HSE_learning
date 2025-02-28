#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#define ll long long

using namespace std;


class HashTable {
private:
    struct Node {
        string key;
        ll value;
        bool is_deleted;
        bool is_empty;
        Node() : key(""), value(0), is_deleted(false), is_empty(true) {}
    };

    vector<Node> table;
    ll q;
    ll p;
    ll mod;

    size_t count_occupied = 0;

    static ll getAlphaPosition(char c) {
        c = tolower(c);
        if (c >= 'a' && c <= 'z') {
            return c - 'a' + 1;
        }
        return 0;
    }

    size_t hash(const string& str) const {
        ll res = 0;
        ll to_pow = 1;
        for (int i = 0; i < str.size(); i++) {
            res += (getAlphaPosition(str[i])) * to_pow;
            to_pow *= p;
        }
        return res % q;
    }

public:
    HashTable(const ll& _q, const ll& _p, const ll& n) : q(_q), p(_p), mod(n) {
        table.resize(n);
    }

    void put(const string& key, const ll& value) {
        size_t h = hash(key);
        size_t sorc_hash = h;
        size_t prob = 0;

        while(!table[h].is_empty && !table[h].is_deleted && table[h].key != key) {
            prob++;
            h = (sorc_hash + prob) % mod;
            if (prob >= mod) {
                cout << "key=" << key << " hash=" << sorc_hash
                     << " operation=PUT result=overflow" << endl;
                return;
            }
        }

        if (!table[h].is_empty && !table[h].is_deleted && table[h].key == key) {
            table[h].value = value;
        } else {
            table[h].key = key;
            table[h].value = value;
            table[h].is_empty = false;
            table[h].is_deleted = false;
            count_occupied++;
        }

        if (prob == 0) {
            cout << "key=" << key << " hash=" << sorc_hash
                 << " operation=PUT result=inserted value=" << value << endl;
        } else {
            cout << "key=" << key << " hash=" << sorc_hash
                 << " operation=PUT result=collision linear_probing=" << h
                 << " value=" << value << endl;
        }
    }

    void get(const string& key) const {
        size_t h = hash(key);
        size_t sorc_hash = h;
        size_t prob = 0;

        while(!table[h].is_empty) {
            if (table[h].key == key && !table[h].is_deleted) {
                if (prob == 0) {
                    cout << "key=" << key << " hash=" << sorc_hash
                         << " operation=GET result=found value=" << table[h].value << endl;
                } else {
                    cout << "key=" << key << " hash=" << sorc_hash
                         << " operation=GET result=collision linear_probing=" << h
                         << " value=" << table[h].value << endl;
                }
                return;
            }
            prob++;
            h = (sorc_hash + prob) % mod;
            if (prob >= mod)
                break;
        }

        if (prob > 0) {
            cout << "key=" << key << " hash=" << sorc_hash
                 << " operation=GET result=collision linear_probing=" << h
                 << " value=no_key" << endl;
        } else {
            cout << "key=" << key << " hash=" << sorc_hash
                 << " operation=GET result=no_key" << endl;
        }
    }

    void del(const string& key) {
        size_t h = hash(key);
        size_t sorc_hash = h;
        size_t prob = 0;

        while(!table[h].is_empty) {
            if (table[h].key == key && !table[h].is_deleted) {
                if (prob == 0) {
                    cout << "key=" << key << " hash=" << sorc_hash
                         << " operation=DEL result=removed" << endl;
                } else {
                    cout << "key=" << key << " hash=" << sorc_hash
                         << " operation=DEL result=collision linear_probing=" << h
                         << " value=removed" << endl;
                }


                table[h].is_deleted = true;
                count_occupied--;
                return;
            }
            prob++;
            h = (sorc_hash + prob) % mod;
            if (prob >= mod) break;
        }

        if (prob > 0) {
            cout << "key=" << key << " hash=" << sorc_hash
                 << " operation=DEL result=collision linear_probing=" << h
                 << " value=no_key" << endl;
        } else {
            cout << "key=" << key << " hash=" << sorc_hash
                 << " operation=DEL result=no_key" << endl;
        }
    }

};

int main() {
    ll q, p, n;
    cin >> q >> p >> n;

    HashTable hp(q, p, q);

    for (ll i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;

        string key;
        cin >> key;

        if (cmd == "PUT") {
            ll value;
            cin >> value;
            hp.put(key, value);
        }
        else if (cmd == "GET") {
            hp.get(key);
        }
        else if (cmd == "DEL") {
            hp.del(key);
        }

    }

    return 0;
}