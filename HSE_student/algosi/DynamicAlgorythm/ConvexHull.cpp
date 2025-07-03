#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
    
    bool operator<(const Point& other) const {
        return (x < other.x) || (x == other.x && y < other.y);
    }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

int swoothPow(Point a, Point b, Point c) {
    int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return points;

    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    n = points.size();
    if (n < 3) return points;

    vector<Point> hull;
    
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i] < points[leftmost]) {
            leftmost = i;
        }
    }

    int p = leftmost, q;
    do {
        hull.push_back(points[p]);
        q = (p + 1) % n;
        
        for (int i = 0; i < n; i++) {
            if (swoothPow(points[p], points[i], points[q]) == 2) {
                q = i;
            }
        }
        
        p = q;
    } while (p != leftmost);

    return hull;
}

int main() {
    vector<Point> points;
    int x, y;
    
    while (cin >> x >> y) {
        points.push_back({x, y});
    }

    vector<Point> hull = convexHull(points);

    cout << "Convex Hull is:\n";
    for (const auto& p : hull) {
        cout << p.x << " " << p.y << "\n";
    }

    return 0;
}