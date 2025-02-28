#include <iostream>
#include <vector>
#include <unistd.h> // для usleep (задержки)

const int WIDTH = 20;
const int HEIGHT = 20;

// Функция для отображения сетки
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << (grid[i][j] ? "O" : ".") << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Функция для подсчета количества живых соседей
int countLiveNeighbors(const std::vector<std::vector<int>>& grid, int x, int y) {
    int liveNeighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Пропускаем текущую клетку
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < HEIGHT && ny >= 0 && ny < WIDTH) {
                liveNeighbors += grid[nx][ny];
            }
        }
    }
    return liveNeighbors;
}

// Функция для обновления состояния сетки
void updateGrid(std::vector<std::vector<int>>& grid) {
    std::vector<std::vector<int>> newGrid = grid;

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int liveNeighbors = countLiveNeighbors(grid, i, j);

            if (grid[i][j] == 1) {
                // Клетка жива
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newGrid[i][j] = 0; // Умирает от одиночества или перенаселения
                }
            } else {
                // Клетка мертва
                if (liveNeighbors == 3) {
                    newGrid[i][j] = 1; // Оживает благодаря размножению
                }
            }
        }
    }

    grid = newGrid;
}

int main() {
    // Инициализация сетки
    std::vector<std::vector<int>> grid(HEIGHT, std::vector<int>(WIDTH, 0));

    // Начальная конфигурация (например, "глайдер")
    grid[1][2] = 1;
    grid[2][3] = 1;
    grid[3][1] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;

    while (true) {
        printGrid(grid);
        updateGrid(grid);
        usleep(200000); // Задержка в микросекундах (200000 мкс = 0.2 секунды)
    }

    return 0;
}