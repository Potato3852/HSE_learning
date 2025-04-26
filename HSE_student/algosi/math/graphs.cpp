#include <iostream>
#include <vector>

class Stack {
private:
    struct node {
        int value;
        node* prev;
    };
    node* head;
    int size;

public:
    Stack() : head(nullptr), size(0) {};

    ~Stack() {
        while(head != nullptr) {
            node* temp = head->prev;
            delete head;
            head = temp;
        }
    }

    void push(int value) {
        node* newNode = new node{value, head};
        head = newNode;
        ++size;
    }

    int pop() {
        if (isEmpty()) {
            throw std::runtime_error("Стек пуст");
        }
        
        int result = head->value;
        node* oldHead = head;
        head = head->prev;
        delete oldHead;
        --size;
        return result;
    }

    bool find(int a) {
        node* temp = head;
        if(isEmpty()) {
            throw std::runtime_error("Стек пуст");
        } else {
            while(temp != nullptr) {
                if(temp->value == a) {
                    return true;
                }
                temp = temp->prev;
            }
            return false;
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    int top() {
        return head->value;
    }

    void print() {
        node* temp = head;
        while(temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }
};
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

    bool find(int a) {
        if (isEmpty()) {
            return false;
        }

        Node* temp = front;
        while (temp != nullptr) {
            if (temp->value == a) {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    int peek() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста");
        }

        return front->value;
    }

    void print() {
        Node* temp = front;
        while (temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};
class MinHeap {
private:
    std::vector<std::pair<int, int>> heap; // pair<distance, vertex>

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent].first > heap[index].first) {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int left, right, smallest;
        while (true) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;

            if (left < heap.size() && heap[left].first < heap[smallest].first)
                smallest = left;
            if (right < heap.size() && heap[right].first < heap[smallest].first)
                smallest = right;

            if (smallest != index) {
                std::swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    void push(int distance, int vertex) {
        heap.emplace_back(distance, vertex);
        heapifyUp(heap.size() - 1);
    }

    std::pair<int, int> pop() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        std::pair<int, int> top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return top;
    }

    bool isEmpty() const { return heap.empty(); }
    size_t size() const { return heap.size(); }
};

class Graph {
private:
    bool isDirected;
    std::vector<std::vector<int>> list;
    std::vector<std::vector<int>> weights;
    struct Edge { int u, v, weight; };

    bool contains(const std::vector<int>& vec, int value) const {
        for (int item : vec) {
            if (item == value) return true;
        }
        return false;
    }

    void removeFromVector(std::vector<int>& vec, int value) {
        for (size_t i = 0; i < vec.size(); ++i) {
            if (vec[i] == value) {
                vec.erase(vec.begin() + i);
                return;
            }
        }
    }

    std::vector<Edge> getAllEdges() const {
        std::vector<Edge> edges;
        for (int u = 0; u < vertexCount(); ++u) {
            for (int v : list[u]) {
                if (!isDirected || u < v) // Чтобы не дублировать рёбра
                    edges.push_back({u, v, weights[u][v]});
            }
        }
        return edges;
    }

public:
    Graph(int number, bool directed = false) : isDirected(directed) { 
        list.resize(number); 
    }

    void addVertex() {
        list.emplace_back();
    }

    void addEdge(int a, int b) {
        list[a].push_back(b);
        if (!isDirected) {
            list[b].push_back(a);
        }
    }

    void deleteEdge(int a, int b) {
        removeFromVector(list[a], b);
        
        if (!isDirected && a != b) {
            removeFromVector(list[b], a);
        }
    }

    bool hasEdge(int a, int b) const {
        if (a < 0 || b < 0 || a >= list.size() || b >= list.size()) 
            return false;
        return contains(list[a], b);
    }

    size_t vertexCount() const {
        return list.size();
    }

    std::vector<int> DFS(int start) const {
        std::vector<int> traversal;
        std::vector<bool> visited(vertexCount(), false);
        Stack stack;

        stack.push(start);
        visited[start] = true;

        while (!stack.isEmpty()) {
            int current = stack.top();
            stack.pop();
            traversal.push_back(current);

            for (int neighbor : list[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    stack.push(neighbor);
                }
            }
        }

        return traversal;
    }

    std::pair<std::vector<int>, std::vector<int>> BFS(int start) const {
        std::vector<int> traversal;
        std::vector<int> distances(vertexCount(), -1);
        Queue queue;

        queue.push(start);
        distances[start] = 0;

        while (!queue.isEmpty()) {
            int current = queue.pop();
            traversal.push_back(current);

            for (int neighbor : list[current]) {
                if (distances[neighbor] == -1) {
                    distances[neighbor] = distances[current] + 1;
                    queue.push(neighbor);
                }
            }
        }

        return {traversal, distances};
    }

    std::vector<int> dijkstra(int start) const {
        std::vector<int> dist(vertexCount(), INT_MAX);
        MinHeap heap;

        dist[start] = 0;
        heap.push(0, start);

        while (!heap.isEmpty()) {
            auto current = heap.pop();
            int u = current.second;

            for (int v : list[u]) {
                if (dist[v] > dist[u] + weights[u][v]) {
                    dist[v] = dist[u] + weights[u][v];
                    heap.push(dist[v], v);
                }
            }
        }

        return dist;
    }

    std::vector<std::pair<int, int>> primMST() const {
        if (isDirected) return {}; // Прим работает только для неориентированных графов

        std::vector<int> parent(vertexCount(), -1);
        std::vector<int> key(vertexCount(), INT_MAX);
        std::vector<bool> inMST(vertexCount(), false);

        key[0] = 0;

        for (int count = 0; count < vertexCount() - 1; ++count) {
            int u = -1;
            for (int v = 0; v < vertexCount(); ++v) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }

            inMST[u] = true;

            for (int v : list[u]) {
                if (!inMST[v] && weights[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = weights[u][v];
                }
            }
        }

        std::vector<std::pair<int, int>> mst;
        for (int i = 1; i < vertexCount(); ++i) {
            if (parent[i] != -1) {
                mst.emplace_back(parent[i], i);
            }
        }

        return mst;
    }

    std::vector<int> topologicalSort() {
        std::vector<int> inDegree(vertexCount(), 0);
        Queue q;
        std::vector<int> result;
    
        // Подсчёт входящих степеней
        for (int u = 0; u < vertexCount(); ++u)
            for (int v : list[u]) inDegree[v]++;
    
        // Добавляем вершины с нулевой степенью
        for (int u = 0; u < vertexCount(); ++u)
            if (inDegree[u] == 0) q.push(u);
    
        while (!q.isEmpty()) {
            int u = q.pop();
            result.push_back(u);
            for (int v : list[u]) {
                if (--inDegree[v] == 0) q.push(v);
            }
        }
        return result;
    }

    void findComponents() {
        std::vector<bool> visited(vertexCount(), false);
        for (int u = 0; u < vertexCount(); ++u) {
            if (!visited[u]) {
                std::vector<int> component;
                Stack stack;
                stack.push(u);
                visited[u] = true;
                while (!stack.isEmpty()) {
                    int v = stack.pop();
                    component.push_back(v);
                    for (int neighbor : list[v]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            stack.push(neighbor);
                        }
                    }
                }
                // Обработать компоненту
            }
        }
    }

    std::vector<int> bellmanFord(int start) {
        std::vector<int> dist(vertexCount(), INT_MAX);
        dist[start] = 0;
        for (int i = 0; i < vertexCount() - 1; ++i) {
            for (Edge& e : getAllEdges()) {
                if (dist[e.u] != INT_MAX && dist[e.v] > dist[e.u] + e.weight) {
                    dist[e.v] = dist[e.u] + e.weight;
                }
            }
        }
        return dist;
    }
};

int main() {

}