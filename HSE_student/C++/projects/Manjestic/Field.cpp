#include "Field.hpp"
#include "Game.hpp"
#include <iostream>

Field::Field(int width, int height) : width(width), height(height) {
    cells.resize(height, std::vector<Cell>(width));
}

int Field::countAliveNeighbors(int x, int y) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;

            int new_x = (x + j + width) % width;
            int new_y = (y + i + height) % height;

            if (cells[new_y][new_x].isAlive()) {
                ++count;
            }
        }
    }
    return count;
}

void Field::nextGeneration(const Game& game) {
    std::vector<std::vector<Cell>> newCells = cells;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int aliveNeighbors = countAliveNeighbors(x, y);

            if (cells[y][x].isAlive()) {
                if (aliveNeighbors < game.getDeathLimit() || 
                    aliveNeighbors > game.getBirthLimit()) {
                    newCells[y][x].setState(false);
                }
            } else {
                if (aliveNeighbors == game.getBirthLimit()) {
                    newCells[y][x].setState(true);
                }
            }
        }
    }

    cells = newCells;
}

void Field::printField() const {
    const std::string aliveColor = "\033[42m";  // Зелёный фон
    const std::string deadColor = "\033[40m";   // Чёрный фон
    const std::string reset = "\033[0m";        // Сброс стилей

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (cells[y][x].isAlive()) {
                std::cout << aliveColor << " " << reset;
            } else {
                std::cout << deadColor << " " << reset;
            }
        }
        std::cout << std::endl;
    }
}

void Field::placePattern(const std::vector<CellPosition>& pattern) {
    for(const auto& pos : pattern) {
        if(pos.x >= 0 and pos.x < width and pos.y >= 0 and pos.y < height) {
            getCell(pos.x, pos.y).setState(true);
        }
    }
}