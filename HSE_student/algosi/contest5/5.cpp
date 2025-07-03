#include <iostream>
#include <vector>
#include <climits>

using IntMatrix = std::vector<std::vector<int>>;
using PathMatrix = std::vector<std::vector<std::pair<int, int>>>;
using Coord = std::pair<int, int>;

void printResults(const IntMatrix& a, 
                const PathMatrix& b,
                const Coord& start, 
                int n, int m) {
    std::vector<Coord> path;
    Coord cur = {n-1, m-1};
    
    while(cur != start) {
        path.push_back(cur);
        cur = b[cur.first][cur.second];
    }
    path.push_back(start);
    
    std::cout << "Path:\n";
    for(int i = path.size() - 1; i >= 0; --i) {
        std::cout << "(" << path[i].first << "," << path[i].second << ") ";
    }
    std::cout << "\nCoins: " << a[n-1][m-1] << std::endl;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    
    IntMatrix field(n, std::vector<int>(m, 0));
    Coord start;
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            std::string cell;
            std::cin >> cell;
            if(cell == "S") {
                start = {i, j};
            } else {
                field[i][j] = std::stoi(cell);
            }
        }
    }
    
    IntMatrix a(n, std::vector<int>(m));
    PathMatrix b(n, std::vector<Coord>(m, {INT_MIN, INT_MIN}));
    
    a[start.first][start.second] = 0;
    
    for(int i = start.first; i < n; ++i) {
        for(int j = start.second; j < m; ++j) {
            if(i == start.first && j == start.second) continue;

            int down = (i > start.first) ? a[i-1][j] : INT_MIN;
            int right = (j > start.second) ? a[i][j-1] : INT_MIN;
            
            if(down > right) {
                a[i][j] = down + field[i][j];
                b[i][j] = {i-1, j};
            } else if(right > down) {
                a[i][j] = right + field[i][j];
                b[i][j] = {i, j-1};
            } else {
                std::vector<Coord> path_left, path_top;
                Coord cur = {i, j-1};
                while(cur != start) {
                    path_left.push_back(cur);
                    cur = b[cur.first][cur.second];
                }
                path_left.push_back(start);
                
                cur = {i-1, j};
                while(cur != start) {
                    path_top.push_back(cur);
                    cur = b[cur.first][cur.second];
                }
                path_top.push_back(start);
                
                bool choose_left = true;
                for(int k = path_left.size()-1, l = path_top.size()-1; k >= 0 && l >= 0; --k, --l) {
                    if(path_left[k] != path_top[l]) {
                        if(path_left[k].second > path_top[l].second) {
                            choose_left = true;
                            break;
                        } else {
                            choose_left = false;
                            break;
                        }
                    }
                }
                
                if(choose_left) {
                    a[i][j] = right + field[i][j];
                    b[i][j] = {i, j-1};
                } else {
                    a[i][j] = down + field[i][j];
                    b[i][j] = {i-1, j};
                }
            }
        }
    }
    
    printResults(a, b, start, n, m);
}