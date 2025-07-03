#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

int* min_element(int *start, int *end) {
    if (start == end) return end;
    int *min = start++;
    for (; start != end; ++start)
        if (*start < *min) min = start;

    return min;
}

int main() {
    int len_a, len_b, len_c;
    int answer = INT_MAX;
    std::cin >> len_a;
    std::vector<int> A;
    for(int i = 0; i < len_a; ++i) {
        int temp;
        std::cin>>temp;
        A.push_back(temp);
    }

    std::cin >> len_b;
    std::vector<int> B;
    for(int i = 0; i < len_b; ++i) {
        int temp;
        std::cin>>temp;
        B.push_back(temp);
    }

    std::cin >> len_c;
    std::vector<int> C;
    for(int i = 0; i < len_c; ++i) {
        int temp;
        std::cin>>temp;
        C.push_back(temp);
    }

    std::vector<int> trio = {A[0], B[0], C[0]};
    int i = 0, j = 0, k = 0;
    int cur_min, cur_max, cur_diff;

    while(i < len_a and j < len_b and k < len_c) {
        cur_min = std::min({A[i], B[j], C[k]});
        cur_max = std::max({A[i], B[j], C[k]});
        cur_diff = cur_max - cur_min;

        if(cur_diff < answer) {
            answer = cur_diff;
            trio = {A[i], B[j], C[k]};
        } else if (cur_diff == answer) {
            if(A[i] < trio[0]) {
                trio = {A[i], B[j], C[k]};
            } else if (A[i] == trio[0] and B[j] < trio[1]){
                trio = {A[i], B[j], C[k]};
            } else if (A[i] == trio[0] and B[j] == trio[1] and C[k] < trio[2]){
                trio = {A[i], B[j], C[k]};
            }
        }

        if(A[i] == cur_min) {
            ++i;
        } else if(B[j] == cur_min) {
            ++j;
        } else {
            ++k;
        }
    }

    std::cout << "Numbers = " << trio[0] << " " << trio[1] << " " << trio[2] << std::endl;
    std::cout << "Result = " << answer << std::endl;
}