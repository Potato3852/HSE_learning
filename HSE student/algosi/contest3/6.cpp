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

    void printInOrder(int index) {
        if(index > -1) {
            printInOrder(tree[index].left);
            std::cout << tree[index].value << ' ';
            printInOrder(tree[index].right);
        }
    }

    void printPreOrder(int index) {
        if(index > -1) {
            std::cout << tree[index].value << ' ';
            printPreOrder(tree[index].left);
            printPreOrder(tree[index].right);
        }
    }

    void printPostOrder(int index) {
        if(index > -1) {
            printPostOrder(tree[index].left);
            printPostOrder(tree[index].right);
            std::cout << tree[index].value << ' ';
        }
    }

public:
    Tree(int n) { tree.resize(n); }

    void insert(int index, long long int key, int left, int right) {
        tree[index] = {key, left, right};
    }

    void InOrder() {
        printInOrder(0);
        std::cout << std::endl;
    }
    
    void PreOrder() {
        printPreOrder(0);
        std::cout << std::endl;
    }

    void PostOrder() {
        printPostOrder(0);
        std::cout << std::endl;
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

    bst.InOrder();
    bst.PreOrder();
    bst.PostOrder();

    return 0;
}