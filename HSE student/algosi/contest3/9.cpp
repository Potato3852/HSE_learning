#include <iostream>
#include <vector>

class Tree {
private:
    struct node {
        long long int value;
        int left;
        int right;
    };

    std::vector<node> tree;

    bool bst(int node, long long min, long long max) {
        if(node == -1) { return true; }

        long long int key = tree[node].value;
        if(key < min or key > max) { return false; }

        return (bst(tree[node].left, min, key - 1) and bst(tree[node].right, key, max));
    }

public:
    Tree(int n) : tree(n) {}

    void insert(int index, long long int key, int left, int right) {
        tree[index] = {key, left, right};
    }

    void Check() {
        if(tree.empty()) { std::cout << "CORRECT" << std::endl; }
        if(bst(0, -2147483648, 2147483648)){
            std::cout << "CORRECT" << std::endl;
        } else {
            std::cout << "INCORRECT" << std::endl;
        }
    }
};

int main() {

    int n, left, right;
    long long int key;
    std::cin >> n;
    Tree bst(n);

    for(int i = 0; i < n; i++) {
        std::cin >> key >> left >> right;
        bst.insert(i, key, left, right);
    }

    bst.Check();

    return 0;
}