#include <iostream>
#include <vector>
#include <algorithm>

struct line {
    int start, end;
};

bool comparelines(line &a, line &b) {
    return a.end < b.end;
}
void solution(std::vector<line> &lines) {
    std::vector<int> points;
    int cur_point = -1;

    sort(lines.begin(), lines.end(), comparelines);
    
    for (auto line : lines) {
        if (line.start > cur_point or cur_point == -1) {
            cur_point = line.end;
            points.push_back(cur_point);
        }
    }
    
    std::cout << points.size() << std::endl;
    for (auto point : points) {
        std::cout << point << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cin >> n;
    
    std::vector<line> lines;
    for (int i = 0; i < n; ++i) {
        line temp;
        std::cin >> temp.start >> temp.end;
        lines.push_back(temp);
    }
    
    solution(lines); 
}