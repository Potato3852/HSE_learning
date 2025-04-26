#include <iostream>
#include <algorithm>
#include <iomanip>

class Tree {
private:
    struct node {
        int value;
        int height;
        node* left;
        node* right;

        explicit node(int val) : value(val), height(1), left(nullptr), right(nullptr) {}
    };

    node *root;
    int size;

public:
    Tree() : root(nullptr), size(0) {}

    ~Tree() {
        deleteTree(root);
    }

    int getSize() {return size;}
    int getRootValue() {return root ? root->value : -1;}
    node* getHead() {return root;}
    void printAsArray() {printInOrder(root); std::cout << std::endl;}

    void insert(int value) {
        root = insertNode(root, value);
        size++;
    }

    void remove(int value) {
        if(root == nullptr || find(root, value) == nullptr) {
            std::cout << "Error: element not found." << std::endl;
            return;
        }
    
        root = removeNode(root, value);
        size--;
    }

    void printTree(node* current, int indent = 0) {
        if (current != nullptr) {
            printTree(current->right, indent + 4);
            
            std::cout << std::setw(indent) << "" << current->value << std::endl;
            
            printTree(current->left, indent + 4);
        }
    }

private:
    void deleteTree(node* current) {
        if(current != nullptr) {
            deleteTree(current->left);
            deleteTree(current->right);
            delete current;
        }
    }

    void printInOrder(node* current) {
        if(current != nullptr) {
            printInOrder(current->left);
            std::cout << current->value << ' ';
            printInOrder(current->right);
        }
    }

    node* insertNode(node* current, int value) {
        if(current == nullptr) {
            return new node(value);
        }

        if(value < current->value) {
            current->left = insertNode(current->left, value);
        } else {
            current->right = insertNode(current->right, value);
        }

        return balance(current);
    }

    node* find(node *current, int value) {
        if(current == nullptr || current->value == value) {
            return current;
        }

        if(value < current->value) {
            return find(current->left, value);
        } else {
            return find(current->right, value);
        }
    }

    node* removeNode(node* current, int value) {
        if(current == nullptr) {
            return nullptr;
        }

        if(value < current->value) {
            current->left = removeNode(current->left, value);
        } else if(value > current->value) {
            current->right = removeNode(current->right, value);
        } else {
            if(current->left == nullptr) {
                node* temp = current->right;
                delete current;
                return temp;
            } else if(current->right == nullptr) {
                node* temp = current->left;
                delete current;
                return temp;
            } else {
                node* successor = minValueNode(current->right);
                current->value = successor->value;
                current->right = removeNode(current->right, successor->value);
            }
        }
        return balance(current);
    }

    node* minValueNode(node* current) {
        node* temp = current;
        while(temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }

    int height(node* current) const {
        if(current == nullptr) {
            return 0;
        }
        return current->height;
    }

    int getBalanceFactor(node* current) const {
        if(current == nullptr) {
            return 0;
        }
        return height(current->left) - height(current->right);
    }

    void updateHeight(node* current) {
        if(current != nullptr) {
            current->height = 1 + std::max(height(current->left), height(current->right));
        }
    }

    node* balance(node* current) {
        if(current == nullptr) {
            return current;
        }

        updateHeight(current);

        int balance = getBalanceFactor(current);

        if (balance > 1 && getBalanceFactor(current->left) >= 0) {
            return rotateRight(current);
        }

        if (balance < -1 && getBalanceFactor(current->right) <= 0) {
            return rotateLeft(current);
        }

        if (balance > 1 && getBalanceFactor(current->left) < 0) {
            current->left = rotateLeft(current->left);
            return rotateRight(current);
        }

        if (balance < -1 && getBalanceFactor(current->right) > 0) {
            current->right = rotateRight(current->right);
            return rotateLeft(current);
        }

        return current;
    }

    node* rotateLeft(node* current) {
        node *rightChild = current->right;
        node *rightChildLeft = rightChild->left;

        rightChild->left = current;
        current->right = rightChildLeft;

        updateHeight(current);
        updateHeight(rightChild);

        return rightChild;
    }

    node* rotateRight(node* current) {
        node* leftChild = current->left;
        node* leftChildRight = leftChild->right;

        leftChild->right = current;
        current->left = leftChildRight;

        updateHeight(current);
        updateHeight(leftChild);

        return leftChild;
    }
};

int main() {
    Tree bst;
    for(int i = 0; i < 10; ++i) {
        bst.insert(i);
    }
    bst.printTree(bst.getHead());
    std::cout << "-----------------------------------------------" << std::endl;
    bst.remove(7);
    bst.printTree(bst.getHead());
    bst.printAsArray();
    std::cout << "Root: " << bst.getRootValue() << std::endl;


    return 0;
}