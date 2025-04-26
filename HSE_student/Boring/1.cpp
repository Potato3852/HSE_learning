#include<iostream>
#include<vector>
#include<algorithm>

int main() {
    int v,e;
    std::cin >> v >> e;
    std::vector<std::vector<int>> list_of_links(v+1);
    int a, b, aim = 1;
    for(int i = 0; i < e; ++i) {
        std::cin >> a >> b;
        list_of_links[a].push_back(b);
        if (a != b) {
            list_of_links[b].push_back(a);
        }
    }
    std::cout << aim << std::endl;
    std::sort(list_of_links[aim].begin(), list_of_links[aim].end());
    for(int it : list_of_links[aim]) {
        std::cout << it << " ";
    }
    return 0;
}