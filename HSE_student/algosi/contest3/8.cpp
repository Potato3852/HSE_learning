#include <iostream>
#include <vector>

class Tree {
private:
    std::vector<std::vector<int>> stick;
    int root;

    int height(int node) {
        int Max = 0;
        for(int temp : stick[node]) {
            int h = height(temp);
            if(h > Max) {
                Max = h;
            }
        }
        return Max + 1;
    }

public:
    Tree(int n) : stick(n), root(-1) {}

    void CreateTree(const std::vector<int>& tree) {
        for(int i = 0; i < tree.size(); ++i) {
            if(tree[i] == -1) {
                root = i;
            } else {
                stick[tree[i]].push_back(i);
            }
        }
    }

    int getHeight() {
        return height(root);
    }
};

int main() {
    int n;
    std::cin >> n;
    
    std::vector<int> array(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    Tree bst(n);
    bst.CreateTree(array);
    std::cout << bst.getHeight() << std::endl;

    return 0;
}