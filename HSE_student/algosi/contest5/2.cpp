#include <iostream>
#include <string>
#include <vector>

class RabinKarp {
private:
    const int AZBUKA = 26;
    int mod;

    int hash(const std::string& s, int start, int length) {
        int hash = 0;
        for(int i = 0; i < length; ++i) {
            hash = (AZBUKA * hash + (s[start + i] - 'a')) % mod;
        }
        return hash;
    }

public:
    RabinKarp(int modulus) : mod(modulus) {}

    void search(const std::string& text, const std::string& pattern) {
        int n = text.size(), m = pattern.size();
        std::vector<int> matches, kostil;

        if(n < m || m == 0) {
            std::cout << "Matches: \nSpurious hits: \n";
            return;
        }

        int h = 1;
        for(int i = 0; i < m - 1; ++i) {
            h = (h * AZBUKA) % mod;
        }

        int pattern_hash = hash(pattern, 0, m);
        int text_hash = hash(text, 0, m);

        for(int i = 0; i <= n - m; ++i) {
            if(pattern_hash == text_hash) {
                if(text.substr(i, m) == pattern) {
                    matches.push_back(i);
                } else {
                    kostil.push_back(i);
                }
            }

            if(i < n - m) {
                text_hash = (AZBUKA * (text_hash - (text[i] - 'a') * h) + (text[i + m] - 'a')) % mod;
                if(text_hash < 0) 
                    text_hash += mod;
            }
        }

        auto print_vector = [](const std::string& label, const std::vector<int>& v) {
            std::cout << label;
            for(size_t i = 0; i < v.size(); ++i) {
                if (i != 0)
                    std::cout << " ";
                std::cout << v[i];
            }
            std::cout << "\n";
        };

        print_vector("Matches: ", matches);
        print_vector("Spurious hits: ", kostil);
    }
};

int main() {
    int mod;
    std::string pattern, text;
    
    std::cin >> mod >> pattern;
    std::cin.ignore();
    std::cin >> text;

    RabinKarp searcher(mod);
    searcher.search(text, pattern);

    return 0;
}