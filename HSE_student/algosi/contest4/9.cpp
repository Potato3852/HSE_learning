//-Как поймать тигра в клетку?
//-Никак, тигры бывают только в полоску.
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>

class Queue {
private:
    struct Node {
        int value;
        Node* next;
    };

    Node* front;
    Node* back; 
    int size;

public:
    Queue() : front(nullptr), back(nullptr), size(0) {}

    ~Queue() {
        while (front != nullptr) {
            Node* temp = front->next;
            delete front;
            front = temp;
        }
    }

    void push(int value) {
        Node* newNode = new Node{value, nullptr};

        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->next = newNode;
            back = newNode;
        }

        ++size;
    }

    int pop() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }

        int result = front->value;
        Node* oldFront = front;
        front = front->next;
        delete oldFront;

        if (front == nullptr) {
            back = nullptr;
        }

        --size;
        return result;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return front->value;
    }
};

class Graph {
private:
    std::unordered_map<int, std::vector<int>> list;
    int start;
    int end;
    int rows;
    int cols;

public:
    Graph(int row_size, int col_size, const std::vector<std::string>& lab) 
        : start(-1), end(-1), rows(row_size), cols(col_size) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    int cell = i * cols + j;
                    if (lab[i][j] == 'S') {
                        start = cell;
                    } else if (lab[i][j] == 'F') {
                        end = cell;
                    }
    
                    if (lab[i][j] == '#') {
                        list[cell] = {};
                        continue;
                    }
    
                    std::vector<int> neighbors;
                    int di[] = {-1, 0, 1, 0};
                    int dj[] = {0, 1, 0, -1};
                    for (int k = 0; k < 4; ++k) {
                        int ni = i + di[k];
                        int nj = j + dj[k];
                        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && 
                            lab[ni][nj] != '#') {
                            neighbors.push_back(ni * cols + nj);
                        }
                    }
                    std::sort(neighbors.begin(), neighbors.end());
                    list[cell] = neighbors;
                }
            }
        }

    void printGraph() const {
        std::map<int, std::vector<int>> sorted_list(list.begin(), list.end());
        
        for (auto [cell, link] : sorted_list) {
            std::cout << cell << " - ";
            if (link.empty()) {
                std::cout << "None";
            } else {
                for (size_t i = 0; i < link.size(); ++i) {
                    if (i != 0) std::cout << " ";
                    std::cout << link[i];
                }
            }
            std::cout << std::endl;
        }
    }

    void BFS() const {
        std::vector<int> longs(rows * cols, -1);
        
        if (start == -1) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (j != 0) std::cout << " ";
                    std::cout << -1;
                }
                std::cout << std::endl;
            }
            return;
        }
    
        Queue q;
        q.push(start);
        longs[start] = 0;

        while (!q.isEmpty()) {
            int current = q.pop();
            if (current == end) break;
    
            for (int it : list.at(current)) {
                if (longs[it] == -1) {
                    longs[it] = longs[current] + 1;
                    q.push(it);
                }
            }
        }
        std::cout << "BFS result is:" << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int cell = i * cols + j;
                if (j != 0) std::cout << " ";
                std::cout << longs[cell];
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int row, col;
    std::cin >> row >> col;

    std::vector<std::string> lab(row);
    for (int i = 0; i < row; ++i) {
        std::string str;
        std::cin >> str;
        lab[i] = str;
    }
    std::cout << "Initial labyrinth:" << std::endl;
    for (auto row : lab) {
        std::cout << row << std::endl;
    }
    Graph graph(row, col, lab);

    std::cout << "Graph:" << std::endl;
    graph.printGraph();
    graph.BFS();
}