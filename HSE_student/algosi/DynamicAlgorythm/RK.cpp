#include <iostream>
#include <string>
#include <vector>
using namespace std;

void RabinKarpSearch(const string& text, const string& pattern, int mod) {
    int n = text.length();
    int m = pattern.length();
    vector<int> matches;
    vector<int> spurious_hits;

    if (n < m || m == 0) {
        cout << "Matches: \nSpurious hits: \n";
        return;
    }

    int h = 1;
    for (int i = 0; i < m - 1; ++i)
        h = (h * 256) % mod;

    int pattern_hash = 0;
    int text_hash = 0;
    for (int i = 0; i < m; ++i) {
        pattern_hash = (256 * pattern_hash + pattern[i]) % mod;
        text_hash = (256 * text_hash + text[i]) % mod;
    }

    for (int i = 0; i <= n - m; ++i) {
        if (pattern_hash == text_hash) {
            bool match = true;
            for (int j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                matches.push_back(i);
            } else {
                spurious_hits.push_back(i);
            }
        }

        if (i < n - m) {
            text_hash = (256 * (text_hash - text[i] * h) + text[i + m]) % mod;
            if (text_hash < 0)
                text_hash += mod;
        }
    }

    cout << "Matches: ";
    for (size_t i = 0; i < matches.size(); ++i) {
        if (i != 0) cout << " ";
        cout << matches[i];
    }
    cout << "\nSpurious hits: ";
    for (size_t i = 0; i < spurious_hits.size(); ++i) {
        if (i != 0) cout << " ";
        cout << spurious_hits[i];
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int mod;
    string pattern, text;
    
    cin >> mod;
    cin >> pattern;
    cin.ignore();
    getline(cin, text);

    RabinKarpSearch(text, pattern, mod);

    return 0;
}