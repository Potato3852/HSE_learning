#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <climits>

class MinHeap {
private:
    std::vector<std::pair<double, int>> heap; // distance, vertex index

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
    void push(double distance, int vertex) {
        heap.emplace_back(distance, vertex);
        heapifyUp(heap.size() - 1);
    }

    std::pair<double, int> pop() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        std::pair<double, int> top = heap[0];
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
    struct City {
        std::string name;
        int x, y;
    };

    struct Edge {
        int to;
        double weight;
    };

    bool isDirected;
    
    std::vector<std::vector<Edge>> adjacencyList;
    std::unordered_map<std::string, int> nameToIndex;
    std::vector<std::string> indexToName;

public:
    std::vector<City> cities;
    Graph(bool directed = false) : isDirected(directed) {}

    int addCity(const std::string& name, int x, int y) {
        if (nameToIndex.find(name) != nameToIndex.end()) {
            return nameToIndex[name];
        }
        int index = indexToName.size();
        nameToIndex[name] = index;
        indexToName.push_back(name);
        cities.push_back({name, x, y});
        adjacencyList.emplace_back();
        return index;
    }

    void addEdge(const std::string& from, const std::string& to, double weight) {
        int fromIndex = getIndexByName(from);
        int toIndex = getIndexByName(to);
        adjacencyList[fromIndex].push_back({toIndex, weight});
        if (!isDirected) {
            adjacencyList[toIndex].push_back({fromIndex, weight});
        }
    }

    int getIndexByName(const std::string& name) const {
        auto it = nameToIndex.find(name);
        if (it == nameToIndex.end()) {
            throw std::runtime_error("City not found: " + name);
        }
        return it->second;
    }

    std::string getNameByIndex(int index) const {
        return indexToName[index];
    }

    size_t vertexCount() const {
        return indexToName.size();
    }

    std::pair<std::vector<double>, std::vector<int>> dijkstra(const std::string& startName) const {
        int start = getIndexByName(startName);
        std::vector<double> dist(vertexCount(), INT_MAX);
        std::vector<int> prev(vertexCount(), -1);
        MinHeap heap;

        dist[start] = 0;
        heap.push(0, start);

        while (!heap.isEmpty()) {
            auto current = heap.pop();
            int u = current.second;
            double currentDist = current.first;

            if (currentDist > dist[u]) continue;

            for (const Edge& edge : adjacencyList[u]) {
                int v = edge.to;
                double newDist = dist[u] + edge.weight;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    heap.push(newDist, v);
                }
            }
        }

        return {dist, prev};
    }

    double calculateDistance(const City& c1, const City& c2) const {
        return std::sqrt(std::pow(c1.x - c2.x, 2) + std::pow(c1.y - c2.y, 2));
    }

    std::vector<std::string> getPath(const std::vector<int>& prev, const std::string& endName) const {
        std::vector<std::string> path;
        int current = getIndexByName(endName);
        
        while (current != -1) {
            path.push_back(getNameByIndex(current));
            current = prev[current];
        }
        
        std::reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int n;
    Graph graph(false);
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::vector<std::string>> temp;

    for(int i = 0; i < n; ++i) {
        std::string line;
        getline(std::cin, line);
        std::istringstream iss(line);

        std::string city;
        double x, y;
        iss >> city >> x >> y;
        graph.addCity(city, x, y);

        std::vector<std::string> neighbors;
        std::string neighbor;
        while(iss >> neighbor) {
            neighbors.push_back(neighbor);
        }
        temp.push_back(neighbors);
    }

    for(int i = 0; i < n; ++i) {
        std::string city = graph.getNameByIndex(i);
        for (const auto& it : temp[i]) {
            const auto& city1 = graph.getIndexByName(city);
            const auto& city2 = graph.getIndexByName(it);
            double distance = std::sqrt(
                std::pow(graph.cities[city1].x - graph.cities[city2].x, 2) +
                std::pow(graph.cities[city1].y - graph.cities[city2].y, 2)
            );
            graph.addEdge(city, it, distance);
        }
    }

    std::string start, end;
    std::cin >> start >> end;

    try {
        auto [distances, prev] = graph.dijkstra(start);
        auto path = graph.getPath(prev, end);

        if (distances[graph.getIndexByName(end)] == INT_MAX) {
            std::cout << "Path:\nNo way" << std::endl;
        } else {
            double totalDistance = distances[graph.getIndexByName(end)];
            int roundedDistance = static_cast<int>(std::ceil(totalDistance));
            
            std::cout << "Path is not greater than " << roundedDistance << std::endl;
            std::cout << "Path:" << std::endl;
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i] << " ";
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Path:\nNo way" << std::endl;
    }

    return 0;
}