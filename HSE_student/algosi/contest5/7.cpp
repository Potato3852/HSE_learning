#include <iostream>
#include <vector>
#include <climits>

void PrintAnswer(int min_len, int best_sum, int start, int end){
    if(min_len == INT_MAX) {
        std::cout << "No summ\n";
    } else {
        std::cout << "Length = " << min_len << std::endl
                  << "Sum = " << best_sum << std:: endl
                  << "Start = " << start << std::endl
                  << "Finish = " << end << std::endl;
    }
}

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> array;
    for(int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        array.push_back(temp);
    }

    int best_sum = 0;
    int start = -1;
    int end = -1;
    int min_len = INT_MAX;
    int cur_sum = 0;
    int l = 0;

    for(int r = 0; r < n; ++r) {
        cur_sum+= array[r];

        while(cur_sum >= k) {
            int cur_len = r - l + 1;

            if(cur_len < min_len or (cur_len == min_len and cur_sum > best_sum) or (cur_len == min_len and cur_sum == best_sum and l < start)) {
                start = l;
                end = r;
                best_sum = cur_sum;
                min_len = cur_len;
            }

            cur_sum -= array[l];
            l++;
        }
    }

    PrintAnswer(min_len, best_sum, start, end);
}