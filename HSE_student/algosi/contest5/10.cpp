#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<sstream>
#include<ctime>
#include<windows.h>
#define Kostil = 10000;

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int SmoothPow(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

double Distance(const Point& a, const Point& b) {
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

void ConvexHull(std::vector<Point>& points, std::vector<Point>& body) {
    int n = points.size();
    if(n < 2) return;

    auto it = std::min_element(points.begin(), points.end());
    std::iter_swap(points.begin(), it);
    Point pivo = points[0];

    std::sort(points.begin() + 1, points.end(), [&pivo](const Point& a, const Point& b) {
        int cross = SmoothPow(pivo, a, b);
        if(cross != 0)
            return cross > 0;
        return Distance(pivo, a) < Distance(pivo, b);
    });

    if(n < 2) return;

    body.push_back(points[0]);
    if(n >= 2) body.push_back(points[1]);

    for(int i = 2; i < n; i++) {
        while(body.size() >= 2 and
              SmoothPow(body[body.size()-2], body.back(), points[i]) <= 0) {
            body.pop_back();
        }
        body.push_back(points[i]);
    }

    std::sort(body.begin(), body.end());

    if(n < 2) return;

    std::cout << "Convex Hull is:" << std::endl;
    for(auto p : body) {
        std::cout << p.x << " " << p.y << std::endl;
    }

    if(n < 2) return;
}

int main() {
    std::vector<Point> points;
    int x, y;
    std::string line;

    while(std::getline(std::cin, line)) {
        if(line.empty()) break;

        std::stringstream ss(line);
        if(ss >> x >> y) {
            points.push_back({x, y});
        }
    }

    std::vector<Point> body;
    ConvexHull(points, body);

    _sleep(20000);
}

// Илья сергеевич, поехали в сауну)