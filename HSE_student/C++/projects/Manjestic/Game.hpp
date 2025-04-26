#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <vector>
#include <map>

struct CellPosition {
    int x, y;
};

class Game {
private:
    int width, height;
    int birthLimit;
    int deathLimit;
    std::map<std::string, std::vector<CellPosition>> patterns;

public:
    void loadFromFile(const std::string& filename);

    std::vector<CellPosition> getPattern(const std::string& name) const;

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getBirthLimit() const { return birthLimit; }
    int getDeathLimit() const { return deathLimit; }
};

#endif // GAME_HPP