#include <iostream>
#include <vector>

void Fun(std::vector<int>& array, int n){
    std::vector<int> a(n, 1);
    std::vector<int> b(n, -1);
    int max = 1;
    
    int best = 0;
    for(int i = 1; i < n; ++i) {
        for(int j = i - 1; j >= 0; --j) {
            if(array[j] <= array[i] and a[j] > a[i] - 1) {
                b[i] = j;
                a[i] = a[j] + 1;
            }
        }
        if(a[i] >= max or (a[i] == max and i > best)) {
            max = a[i];
            best = i;
        }
    }

    std::vector<int> answer;
    for (int i = best; i != -1; i = b[i]) {
        answer.push_back(array[i]);
    }
    
    std::cout << "Best length = " << max << std::endl << "Best combo is:  ";
    for(auto it = answer.rbegin(); it != answer.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> array;

    for(int i = 0; i < n; ++i){
        int temp;
        std::cin >> temp;
        array.push_back(temp);
    }

    Fun(array, n);
}