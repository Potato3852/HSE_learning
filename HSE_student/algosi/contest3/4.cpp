#include <iostream>
#include <vector>

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> size;
    int maxS;
public:
    DSU(int n, const std::vector<int>& sizes) {
        parent.resize(n);
        size.resize(n);
        maxS = 0;
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            size[i] = sizes[i];
            if (size[i] > maxS) {
                maxS = size[i];
            }
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int a, int b) {
        int root1 = find(a);
        int root2 = find(b);

        if (root1 != root2) {
            if (size[root1] > size[root2]) {
                int temp = root1;
                root1 = root2;
                root2 = temp;
            } 
            parent[root2] = root1;
            size[root1] += size[root2];
            if(size[root1] > maxS) {
                maxS = size[root1];
            }
        }
    }

    int getMax() {
        return maxS;
    }
};


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> sizes(n);
    for(int i = 0; i < n; i++) {
        std::cin >> sizes[i];
    }

    DSU dsu(n, sizes);

    for(int i = 0; i < m; i++) {
        int dest, source;
        std::cin >> dest >> source;
        dsu.unite(dest - 1, source - 1);
        std::cout << dsu.getMax() << std::endl;
    }

    return 0;
}