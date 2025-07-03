#include <iostream>
#include <vector>
#include <string>
#define ll long long int

std::vector<ll> PreFunction(const std::string& s) {
    ll n = s.length();
    std::vector<ll> pi(n);
    ll k = 0;
    
    for(ll q = 1; q < n; ++q) {
        while (k > 0 && s[k] != s[q]) 
            k = pi[k-1];
        if (s[k] == s[q]) 
            k++;
        pi[q] = k;
    }
    return pi;
}

std::vector<ll> KMPSearch(const std::string& t, const std::string& p) {
    ll n = t.length();
    ll m = p.length();
    auto pi = PreFunction(p);
    std::vector<ll> res;
    ll q = 0;
    
    for(ll i = 0; i < n; ++i) {
        while(q > 0 && p[q] != t[i])
            q = pi[q-1];
        if(p[q] == t[i])
            q++;
        if(q == m) {
            res.push_back(i-m+1);
            q = pi[q-1];
        }
    }
    return res;
}

int main() {
    std::string a, b;
    std::cin >> a >> b;

    auto pt = PreFunction(a);
    std::cout << "Prefix template:";
    for(auto x : pt) std::cout << " " << x;
    std::cout << "\n";

    auto ext = a + "#" + b;
    auto pf = PreFunction(ext);
    std::cout << "Prefix function:";
    for(auto x : pf) std::cout << " " << x;
    std::cout << "\n";

    auto m = KMPSearch(b, a);
    std::cout << "Matches:";
    for(auto x : m) std::cout << " " << x;
    std::cout << "\n";
}