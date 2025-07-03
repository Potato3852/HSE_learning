#include <iostream>
#include <vector>
#include <string>
#include <climits>

int Distance(std::string a, std::string b) {
    int m = a.size(), n = b.size();
    int d[m+1][n+1];
    
    for(int i = 0; i <= m; i++)
        d[i][0] = i;
    for(int j = 0; j <= n; j++)
        d[0][j] = j;

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            int cost = (a[i-1] == b[j-1]) ? 0 : 1;
            int temp = d[i-1][j-1] + cost;
            if(d[i-1][j] + 1 < temp) temp = d[i-1][j] + 1;
            if(d[i][j-1] + 1 < temp) temp = d[i][j-1] + 1;
            d[i][j] = temp;
        }
    }
    return d[m][n];
}

void Result(std::vector<std::string> result, int min_diff) {
    std::cout << "Most similar words = " << result.size() << "\n";
    std::cout << "Minimal operations needed = " << min_diff << "\n";
    
    for(size_t i = 0; i < result.size(); i++) {
        if(i != 0) std::cout << "\n";
        std::cout << result[i];
    }
}

int main() {
    std::string target;
    std::cin >> target;
    
    int n;
    std::cin >> n;
    
    std::vector<std::string> words;
    std::vector<int> diffs;
    int min_diff = INT_MAX;
    
    for(int i = 0; i < n; i++) {
        std::string word;
        std::cin >> word;

        int diff = Distance(target, word);
        diffs.push_back(diff);
        if(diff < min_diff) min_diff = diff;
        
        words.push_back(word);
    }
    
    std::vector<std::string> result;
    for(int i = 0; i < n; i++) {
        if(diffs[i] == min_diff) {
            result.push_back(words[i]);
        }
    }
    
    Result(result, min_diff);
}