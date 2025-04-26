#include <iostream>
#include <vector>
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
            throw std::runtime_error("Очередь пуста");
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

    int peek() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста");
        }

        return front->value;
    }
};

class Graph {
    long long size;
    std::vector<std::vector<int>> adj;
    std::vector<int> inDegree;
    
public:
    Graph(int V) : size(V), adj(V), inDegree(V, 0) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        inDegree[v]++;
    }
    
    std::vector<std::vector<int>> topo() {
        std::vector<std::vector<int>> result;
        std::vector<int> current;
        
        auto dfs = [&](auto&& self) -> void {
            if (current.size() == size) {
                result.push_back(current);
                return;
            }
            
            for (int v = 0; v < size; ++v) {
                if (inDegree[v] == 0) {
                    current.push_back(v);
                    inDegree[v] = -1;
                    for (int neighbor : adj[v]) inDegree[neighbor]--;
                    
                    self(self);
                    
                    for (int neighbor : adj[v]) inDegree[neighbor]++;
                    inDegree[v] = 0;
                    current.pop_back();
                }
            }
        };
        
        dfs(dfs);
        std::sort(result.begin(), result.end());
        return result;
    }
    
    bool hasCycle() {
        Queue q;
        std::vector<int> temp = inDegree;
        int count = 0;
        
        for (int v = 0; v < size; v++) {
            if (temp[v] == 0) {
                q.push(v);
            }
        }
        
        while (!q.isEmpty()) {
            int u = q.peek();
            q.pop();
            count++;
            
            for (int v : adj[u]) {
                if (--temp[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        return count != size;
    }
};

int main() {
    int V;
    std::cin >> V;
    Graph g(V);
    
    for (int u = 0; u < V; u++) {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; j++) {
            int v;
            std::cin >> v;
            g.addEdge(u, v);
        }
    }
    
    if (g.hasCycle()) {
        std::cout << "Impossible" << std::endl;
        return 0;
    }
    
    std::vector<std::vector<int>> allOrders = g.topo();
    
    std::cout << allOrders.size() << std::endl;
    for (const auto& order : allOrders) {
        for (int v : order) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}