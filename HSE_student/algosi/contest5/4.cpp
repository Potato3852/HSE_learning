#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

class Heap {
private:
    std::vector<Node*> array;

    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int size = array.size();

        auto shouldSwap = [&](Node* a, Node* b) {
            return a->freq < b->freq;
        };

        if(left < size and shouldSwap(array[left], array[smallest])) {
            smallest = left;
        }

        if(right < size and shouldSwap(array[right], array[smallest])) {
            smallest = right;
        }

        if(smallest != i) {
            std::swap(array[i], array[smallest]);
            heapify(smallest);
        }
    }

public:
    void insert(Node* key) {
        array.push_back(key);
        int i = array.size() - 1;
        
        auto shouldSwap = [&](Node* parent, Node* child) {
            return parent->freq > child->freq;
        };

        while(i != 0 and shouldSwap(array[(i - 1) / 2], array[i])) {
            std::swap(array[(i - 1) / 2], array[i]);
            i = (i - 1) / 2;
        }
    }

    Node* extractMin() {
        if(array.empty()) return nullptr;

        if(array.size() == 1) {
            Node* root = array[0];
            array.pop_back();
            return root;
        }

        Node* root = array[0];
        array[0] = array.back();
        array.pop_back();
        heapify(0);

        return root;
    }

    size_t size() const {
        return array.size();
    }
};

void encode(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCode) {
    if(root == nullptr) return;
    if(!root->left and !root->right) {
        huffmanCode[root->ch] = str;
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

int main() {
    std::string str;
    std::cin >> str;

    std::unordered_map<char, int> freq;
    for(char ch : str) {
        freq[ch]++;
    }

    Heap heap;
    std::vector<char> order;
    for(char ch : str) {
        if (freq.count(ch)) {
            order.push_back(ch);
            freq.erase(ch);
        }
    }
    freq.clear();
    for(char ch : str) freq[ch]++;
    for(char ch : order) {
        heap.insert(new Node(ch, freq[ch]));
    }

    if(heap.size() == 1) {
        Node* root = heap.extractMin();
        std::unordered_map<char, std::string> huffman;
        huffman[root->ch] = "0";
        
        std::string encodedStr;
        for (char ch : str) {
            encodedStr += huffman[ch];
        }
        
        std::cout << 1 << " " << encodedStr.size() << std::endl;
        std::cout << root->ch << ": 0" << std::endl;
        std::cout << encodedStr << std::endl;
        
        delete root;
        return 0;
    }

    while(heap.size() > 1) {
        Node* left = heap.extractMin();
        Node* right = heap.extractMin();
        Node* newNode = new Node('\0', left->freq + right->freq);
        
        newNode->left = left;
        newNode->right = right;
        heap.insert(newNode);
    }

    Node* root = heap.extractMin();
    std::unordered_map<char, std::string> huffman;
    encode(root, "", huffman);

    std::string answer;
    for(char ch : str) {
        answer += huffman[ch];
    }

    std::cout << freq.size() << " " << answer.size() << std::endl;
    
    std::vector<char> chars;
    for(char ch : str) {
        if(huffman.count(ch) && 
            std::find(chars.begin(), chars.end(), ch) == chars.end()) {
            chars.push_back(ch);
        }
    }
    
    for(char ch : chars) {
        std::cout << ch << ": " << huffman[ch] << std::endl;
    }
    std::cout << answer << std::endl;

    return 0;
}