#include <iostream>
#include <vector>
#include <climits>

class Graph {
private:
    std::vector<std::vector<long long>> matrix;
    int n;
    long long minCost;
    std::vector<int> bestPath;

    bool findAnswer(int start, std::vector<int>& path, long long& total) {
        std::vector<bool> visited(n, false);
        path.clear();
        total = 0;
        
        int current = start;
        path.push_back(current);
        visited[current] = true;
        
        for (int step = 1; step < n; ++step) {
            long long minEdge = LLONG_MAX;
            int nextCity = -1;
            
            for (int i = 0; i < n; ++i) {
                if (!visited[i] && matrix[current][i] > 0 && matrix[current][i] < minEdge) { //Надо лучше проверить
                    minEdge = matrix[current][i];
                    nextCity = i;
                }
            }
            
            if (nextCity == -1) return false;
            
            visited[nextCity] = true;
            path.push_back(nextCity);
            total += minEdge;
            current = nextCity;
        }
        
        if (matrix[current][start] == 0) return false;
        total += matrix[current][start];
        return true;
    }

public:
    Graph(const std::vector<std::vector<long long>>& matrix) 
        : matrix(matrix), n(matrix.size()), minCost(LLONG_MAX) {}

    std::pair<long long, std::vector<int>> tsp() {
        bestPath.clear();
        
        for (int start = 0; start < n; ++start) {
            std::vector<int> path;
            long long cost;
            
            if (findAnswer(start, path, cost)) {
                if (cost < minCost) {
                    minCost = cost;
                    bestPath = path;
                    bestPath.push_back(start);
                }
            }
        }
        
        return { (minCost == LLONG_MAX) ? -1 : minCost, bestPath };
    }
};

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<long long>> matrix(n, std::vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    Graph g(matrix);
    auto answer = g.tsp();
    
    if (answer.first == -1 || answer.second.empty()) {
        std::cout << "Lost" << std::endl;
    } else {
        std::cout << "Path:" << std::endl;
        for (size_t i = 0; i < answer.second.size(); ++i) {
            if (i > 0) std::cout << " ";
            std::cout << answer.second[i];
        }
        std::cout << std::endl;
        std::cout << "Cost: " << answer.first << std::endl;
    }
}