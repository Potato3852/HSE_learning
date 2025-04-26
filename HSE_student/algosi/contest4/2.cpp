#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Graph{
private:
    int size;
    std::vector<std::vector<int>> matrix;
    std::vector<int> path;
    std::vector<bool> visited;
public:
    Graph(int n) : size(n) {
        matrix.resize(size * size);
        for (int x = 0; x < size; ++x) {
            for (int y = 0; y < size; ++y) {
                int from = number(x, y);
                std::vector<int> moves;

                for (auto i : {-2, -1, 1, 2}) {
                    for(auto j : {-2, -1, 1, 2}) {
                        if(abs(i) + abs(j) == 3) {
                            int new_x = x + i;
                            int new_y = y + j;
                            if (check(new_x, new_y)) {
                                moves.push_back(number(new_x, new_y));
                            }
                        }
                    }
                }
                std::sort(moves.begin(), moves.end());
                matrix[from] = moves;
            }
        }
        visited.resize(size * size, false);
    }

    int number(int x, int y) { return x * size + y; }
    std::pair<int, int> unnumber(int a) { return {a / size, a % size};}
    bool check(int x, int y) { return (x >= 0 and y >= 0 and y < size and x < size);}

    bool dfs(int current, int final = 0) {
        path.push_back(current);
        visited[current] = true;
        
        if (final == size*size - 1) {
            return true;
        }
        
        for (int it : matrix[current]) {
            if (!visited[it] && dfs(it, final + 1)) {
                return true;
            }
        }
        
        path.pop_back();
        visited[current] = false;
        return false;
    }
    void Print() {
        std::cout << "Graph:" << std::endl;
        for (int i = 0; i < size * size; ++i) {
            std::cout << i << " - ";
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (j > 0) std::cout << " ";
                std::cout << matrix[i][j];
            }
            std::cout << std::endl;
        }
    }

    void Path() {
        std::cout << "Hamiltonian path:" << std::endl;
        if (path.empty()) {
            std::cout << "No way" << std::endl;
        } else {
            std::vector<std::vector<int>> board(size, std::vector<int>(size, -1));
            for (int step = 0; step < path.size(); ++step) {
                auto [x, y] = unnumber(path[step]);
                board[x][y] = step;
            }
            
            for (const auto& row : board) {
                for (int y = 0; y < row.size(); ++y) {
                    if (y > 0) std::cout << " ";
                    std::cout << row[y];
                }
                std::cout << std::endl;
            }
        }
    }

};

int main() {
    int size, start_x, start_y;
    std::cin >> size >> start_x >> start_y;
    
    Graph graph(size);
    graph.Print();
    
    int start = graph.number(start_x, start_y);
    if (graph.dfs(start)) {
        graph.Path();
    } else {std::cout << "Hamiltonian path:" << std::endl <<"No way";}
}