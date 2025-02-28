#include <iostream>
#include <vector>

class RBTree {
private:
    struct node {
        int value;
        int color;
        node* left;
        node* right;

        node(int val, int col) : value(val), color(col), left(nullptr), right(nullptr) {}
    };

    node* root;

    bool isRed(node* node) {
        return node != nullptr && node->color == 1;
    }

    bool checkRed(node* node) {
        if (node == nullptr) return true;

        if (isRed(node)) {
            if (isRed(node->left) || isRed(node->right)) {
                return false;
            }
        }
        return checkRed(node->left) && checkRed(node->right);
    }

    int BlackH(node* node) {
        if (node == nullptr) return 1;

        int leftBlackHeight = BlackH(node->left);
        int rightBlackHeight = BlackH(node->right);

        if (leftBlackHeight == -1 || rightBlackHeight == -1 || leftBlackHeight != rightBlackHeight) {
            return -1;
        }
        return leftBlackHeight + (node->color == 0 ? 1 : 0);
    }

    node* buildTree(const std::vector<std::vector<int>>& children, const std::vector<int>& colors, int index) {
        if (index == -1) return nullptr;

        node* newNode = new node(index, colors[index]);
        if (!children[index].empty()) {
            newNode->left = buildTree(children, colors, children[index][0]);
        }
        if (children[index].size() > 1) {
            newNode->right = buildTree(children, colors, children[index][1]);
        }
        return newNode;
    }

public:
    RBTree() : root(nullptr) {}

    void build(const std::vector<std::vector<int>>& children, const std::vector<int>& colors, int rootIndex) {
        root = buildTree(children, colors, rootIndex);
    }

    void isRedBlackTree() {
        if (root == nullptr) {
            std::cout << "YES" << std::endl;
            return;
        }
        if (isRed(root)) {
            std::cout << "NO" << std::endl;
            return;
        }

        if (!checkRed(root)) {
            std::cout << "NO" << std::endl;
            return;
        }

        if (BlackH(root) == -1) {
            std::cout << "NO" << std::endl;
            return;
        }
        std::cout << "YES" << std::endl;
    }
};

int main() {
    int v;
    std::cin >> v;

    std::vector<int> colors(v);
    std::vector<std::vector<int>> children(v);

    int rootIndex = -1;
    std::vector<bool> isChild(v, false);

    for (int i = 0; i < v; ++i) {
        int numChildren;
        std::cin >> numChildren;

        std::vector<int> childList(numChildren);
        for (int j = 0; j < numChildren; ++j) {
            std::cin >> childList[j];
            isChild[childList[j]] = true;
        }
        int color;
        std::cin >> color;

        colors[i] = color;
        children[i] = childList;
    }

    for (int i = 0; i < v; ++i) {
        if (!isChild[i]) {
            rootIndex = i;
            break;
        }
    }

    RBTree rbt;
    rbt.build(children, colors, rootIndex);
    rbt.isRedBlackTree();
    return 0;
}