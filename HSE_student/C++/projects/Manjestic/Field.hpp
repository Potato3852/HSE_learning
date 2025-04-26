#ifndef FIELD_HPP
#define FIELD_HPP

#include "Cell.hpp"
#include "Game.hpp"
#include <vector>

class Field {
private:
    int width;
    int height;
    mutable int prevFrameHeight = 0;
    std::vector< std::vector<Cell> > cells;

    int countAliveNeighbors(int x, int y) const;

public:
    Field(int width, int height);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    Cell& getCell(int x, int y) { return cells[y][x]; }
    const Cell& getCell(int x, int y) const { return cells[y][x]; }

    void nextGeneration(const Game& game);

    void printField() const;

    void placePattern(const std::vector<CellPosition>& pattern);

    void clear() {
        for(auto& row : cells) {
            for(auto& cell : row) {
                cell.setState(false);
            }
        }
    }
};

#endif // FIELD_HPP