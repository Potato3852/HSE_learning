#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

bool compareX(const Point &a, const Point &b) {
    return a.x < b.x;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // Сортируем точки по x для удобства перебора
    sort(points.begin(), points.end(), compareX);

    double best_a = 0, best_b = 0, best_c = 0;
    double best_rmse = 1e18;

    // Перебираем возможные значения c
    for (int i = 1; i < n; ++i) {
        double c = (points[i-1].x + points[i].x) / 2.0;

        // Вычисляем a и b как средние значения y в каждой группе
        double sum_a = 0, sum_b = 0;
        int count_a = 0, count_b = 0;

        for (int j = 0; j < n; ++j) {
            if (points[j].x < c) {
                sum_a += points[j].y;
                count_a++;
            } else {
                sum_b += points[j].y;
                count_b++;
            }
        }

        double a = sum_a / count_a;
        double b = sum_b / count_b;

        // Вычисляем RMSE
        double rmse = 0;
        for (int j = 0; j < n; ++j) {
            double diff = (points[j].x < c ? a : b) - points[j].y;
            rmse += diff * diff;
        }
        rmse = sqrt(rmse / n);

        // Обновляем лучшее решение
        if (rmse < best_rmse) {
            best_rmse = rmse;
            best_a = a;
            best_b = b;
            best_c = c;
        }
    }

    // Выводим результат с точностью до 6 знаков после запятой
    cout << fixed << setprecision(6);
    cout << best_a << " " << best_b << " " << best_c << endl;

    return 0;
}