#include <iostream>
#include <vector>

using namespace std;

struct Vert {
    int color; // 0 или 1
    vector<int> children;
};

bool checkProperties(vector<Vert>& tree, int root, int& HeightBlack) {
    if (root == -1) {
        HeightBlack = 1; 
        return true;
    }

    //если вершина красная, то дети не черные
    if (tree[root].color == 1) {
        for (int child : tree[root].children) {
            if (tree[child].color == 1) {
                return false;
            }
        }
    }

    // проверка детей
    int leftHeightBl = 0, rightHeightBl = 0;
    int left, right;
    if (tree[root].children.size() > 0)
        left = tree[root].children[0];
    else
        left = -1;
    if (tree[root].children.size() > 1)
        right = tree[root].children[1];
    else
        right = -1;
    

    if (!checkProperties(tree, left, leftHeightBl)) {
        return false;
    }
    if (!checkProperties(tree, right, rightHeightBl)) {
        return false;
    }

   
    if (rightHeightBl != leftHeightBl) {
        return false;
    }

    
    HeightBlack = leftHeightBl + (tree[root].color == 0 ? 1 : 0);

    return true;
}

int main() {
    int V;
    cin >> V;

    vector<Vert> tree(V);
    vector<bool> hasParent(V, false);

    for (int i = 0; i < V; ++i) {
        int numChildren;
        cin >> numChildren;
        tree[i].children.resize(numChildren);
        for (int j = 0; j < numChildren; ++j) {
            cin >> tree[i].children[j];
            hasParent[tree[i].children[j]] = true;
        }
        cin >> tree[i].color;
    }

    //поиск корня
    int root = -1;
    for (int i = 0; i < V; ++i) {
        if (!hasParent[i]) {
            root = i;
            cout << root << endl;
            break;
        }
    }

    //черный ли корен
    if (tree[root].color != 0) {
        cout << "NO" << endl;
        return 0;
    }

    // проверка отсавшихся свойств
    int heightBlack = 0;
    if (checkProperties(tree, root, heightBlack)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}